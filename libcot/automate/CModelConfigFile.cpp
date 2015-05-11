#include "CModelConfigFile.h"

#include "IAction.h"
#include "ICycle.h"
#include "IConverter.h"
#include "ICom.h"
#include "CComFactory.h"
#include "CConverterFactory.h"
#include "CCycleFactory.h"
#include "CActionFactory.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CUnit.h"
#include "CDisplayConf.h"
#include "CModelExtensionCard.h"

#include "qfile.h"
#include "qjsonobject.h"
#include "qlocale.h"
#include "qjsondocument.h"
#include "qjsonvalue.h"
#include "qjsonarray.h"
#include "qdebug.h"
#include "qvariant.h"
#include "qmap.h"
#include "qfileinfo.h"

//à suppirmer
#include "CVariableStream.h"
#include "CVariableMeasure.h"
//

CModelConfigFile::CModelConfigFile(QObject *parent)
	: QObject(parent)
{
	qDebug() << "CModelConfigFile(QObject *parent)";
    QFile jsonFile(QString::fromLocal8Bit(COT_JSON_FILE));
	
    qDebug() << "jsonFile.exists()" << jsonFile.exists();

    if (!jsonFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Couldn't open save file.";
    }
	QFileInfo fileInfo(jsonFile);
	qDebug() << "fileInfo.path()" << fileInfo.absoluteFilePath();
	
    QByteArray jsonData = jsonFile.readAll();
	
	QJsonParseError * jsonError  = new QJsonParseError();
	m_jsonDoc = new QJsonDocument(QJsonDocument::fromJson(jsonData, jsonError));
	if(m_jsonDoc->isEmpty()){
		qDebug() << "m_jsonDoc->isEmpty() " <<m_jsonDoc->isEmpty() ;
		qDebug() << "jsonError " <<jsonError->errorString() ;
		qDebug() << "jsonError offset" <<jsonError->offset ;
		qDebug() << "jsonData " <<jsonData.mid(jsonError->offset, jsonError->offset+60) ;
	}

	QJsonObject jsonObjectAll = m_jsonDoc->object();
   
    //com_automate
     if(jsonObjectAll[QStringLiteral("com_automate")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"com_automate\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayComs = jsonObjectAll[QStringLiteral("com_automate")].toArray();
        foreach(QJsonValue jsonValueCom, jsonArrayComs){
            QVariantMap mapCom = jsonValueCom.toVariant().toMap();
            ICom* com = CComFactory::build(mapCom);
            if(com->getType() != type_com_unknow)
                CAutomate::getInstance()->addCom(com);
        }   
        qDebug() << "mapComs " << CAutomate::getInstance()->getMapComs();
    }

    //extension
    if(jsonObjectAll[QStringLiteral("extensions")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"extensions\"] == QJsonValue::Undefined";
	}
	else {
       QJsonArray jsonArrayExts = jsonObjectAll[QStringLiteral("extensions")].toArray();
        foreach(QJsonValue jsonValueExt, jsonArrayExts){
            QVariantMap mapExt = jsonValueExt.toVariant().toMap();
            if(mapExt.contains(QStringLiteral("name"))){
                CModelExtensionCard* ext = new CModelExtensionCard(mapExt);
                CAutomate::getInstance()->addExtensionCard(mapExt.value(QStringLiteral("name")).toString(), ext);
            }
        }   
        qDebug() << "mapExtCard " << CAutomate::getInstance()->getMapExtensions();
    }

    //Units
    if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
		qDebug() << "jsonObject[\"units\"] == QJsonValue::Undefined";
	}
	else {
        if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
		    qDebug() << "jsonObject[\"units\"] == QJsonValue::Undefined";
	    }
	    else {

            QJsonArray jsonArrayUnits = jsonObjectAll[QStringLiteral("units")].toArray();
            QJsonArray jsonArrayConverters = jsonObjectAll[QStringLiteral("units_convertion")].toArray();
		    foreach(QJsonValue jsonValueUnit, jsonArrayUnits){
			    QVariantMap mapUnit = jsonValueUnit.toVariant().toMap();
                if(!mapUnit[QStringLiteral("name")].isNull()) {
                    CUnit* unit = new CUnit(mapUnit[QStringLiteral("name")].toString()
                                          , mapUnit[tr("fr_FR")].toString());
                    CAutomate::getInstance()->addUnit(unit);
                    foreach(QJsonValue jsonValueConverter, jsonArrayConverters){
                        QVariantMap mapConverter = jsonValueConverter.toVariant().toMap();
                        if(!mapConverter[QStringLiteral("source")].isNull()) {
                            IConverter* converter = CConverterFactory::build(mapConverter);
                            unit->addConverter(mapConverter[QStringLiteral("source")].toString(),converter);
                            
                        }else{
				            qDebug() << "Converter null : map = " << mapConverter;

                        }
                    }
                }else{
                    qDebug() << "Unit null : map = " << mapUnit ;

                }
            }
		}
    }

	//Variables
    if(jsonObjectAll[QStringLiteral("variables")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"variables\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayVariables = jsonObjectAll[QStringLiteral("variables")].toArray();
		foreach(QJsonValue jsonValueVariable, jsonArrayVariables){
			QVariantMap mapVariable = jsonValueVariable.toVariant().toMap();
			IVariable* var = CVariableFactory::build(mapVariable); 
			if(var)
                CAutomate::getInstance()->addVariable(mapVariable[QStringLiteral("name")].toString(),var);
			else 
				qDebug() << "Variables null : map = " << mapVariable;
		}
	}

   

    //display
    if(jsonObjectAll[QStringLiteral("display")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"display\"] == QJsonValue::Undefined";
	}
	else {
       CDisplayConf* displayConf = new CDisplayConf(jsonObjectAll[QStringLiteral("display")].toArray(), CAutomate::getInstance());
       CAutomate::getInstance()->setDisplayConf(displayConf);
    }

	//bind variables
    if(jsonObjectAll[QStringLiteral("variables")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"variables\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayBinds = jsonObjectAll[QStringLiteral("binds")].toArray();
		foreach(QJsonValue jsonValueBind, jsonArrayBinds){
			QVariantMap mapBind = jsonValueBind.toVariant().toMap();
            IVariable* var = CAutomate::getInstance()->getVariable(mapBind[QStringLiteral("variable_origin_name")].toString());
            IVariable* var_binded = CAutomate::getInstance()->getVariable(mapBind[QStringLiteral("variable_destination_name")].toString());
			if(var && var_binded)
				var->addBind(var_binded);
			else 
				qDebug() << "Bind introuvable : map = " << mapBind;
		}
	}

	//Actions
    if(jsonObjectAll[QStringLiteral("actions")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"actions\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayActions = jsonObjectAll[QStringLiteral("actions")].toArray();
		foreach(QJsonValue jsonValueAction, jsonArrayActions){
			QVariantMap mapAction = jsonValueAction.toVariant().toMap();
			IAction* action = CActionFactory::build(mapAction); 
			if(action){
				m_mapActions.insert(action->getName(),action);
                CAutomate::getInstance()->addAction(action);
            }else 
				qDebug() << "Action null : map = " << mapAction;
		}
        qDebug() << "ACTIONS : " << m_mapActions;

	}

	//Cycles
	QJsonObject jsonObjectCycle = m_jsonDoc->object();
    if(jsonObjectCycle[QStringLiteral("cycles")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"cycles\"] == QJsonValue::Undefined";
	}
	else {
        CAutomate *automate = CAutomate::getInstance();
        QJsonArray jsonArrayCycles = jsonObjectCycle[QStringLiteral("cycles")].toArray();
		foreach(QJsonValue jsonValueCycle, jsonArrayCycles){
			QVariantMap mapCycle = jsonValueCycle.toVariant().toMap();
			ICycle* cycle = CCycleFactory::build(mapCycle); 
            if(cycle) {
				m_mapCycles.insert(cycle->getName(),cycle);
                automate->addCycle(cycle);
            }
			else
				qDebug() << "Cycle null : map = " << mapCycle;

            if(cycle)
            qDebug() << "INFO CYCLE : " << cycle->getListSteps();
		}
        qDebug() << "CYCLES : " << m_mapCycles;
	}

	//Séquenceur
	QJsonObject jsonObjectSequenceur = m_jsonDoc->object();
    if(jsonObjectSequenceur[QStringLiteral("scheduler")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"scheduler\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequenceur[QStringLiteral("scheduler")].toArray();
		foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
			QVariantMap mapSequence = jsonValueSequence.toVariant().toMap();
            if(mapSequence[QStringLiteral("cycle")] != QStringLiteral(""))
                m_listSequences.append(m_mapCycles[mapSequence[QStringLiteral("cycle")].toString()]);
			else
				qDebug() << "Sequence name cycle null : map = " << mapSequence;
		}
        qDebug() << "SEQUENCEUR : " << m_listSequences;

	}
	qDebug() << "FIN CModelConfigFile(QObject *parent)";

     //Streams : 
     if(jsonObjectAll[QStringLiteral("streams")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"streams\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayStreams = jsonObjectAll[QStringLiteral("streams")].toArray();
		foreach(QJsonValue jsonValueStream, jsonArrayStreams){
			QVariantMap mapStream = jsonValueStream.toVariant().toMap();
            mapStream.insert(QStringLiteral("type"), QStringLiteral("stream"));
			IVariable* var = CVariableFactory::build(mapStream); 
			if(var)
                CAutomate::getInstance()->addStream(mapStream[QStringLiteral("name")].toString(),var);
			else 
				qDebug() << "Streams null : map = " << mapStream;
		}

        CAutomate* a = CAutomate::getInstance();
        foreach(IVariable* varStream, a->getMapStreams()){
            CVariableStream* stream = (CVariableStream*)varStream;
            qDebug() << "-stream label : " << stream->getLabel(); 
            qDebug() << "-stream active : " << stream->getActiveState()->getLabel() << " " << stream->getActiveState()->toBool(); 
            foreach(IVariable* varMeasure, stream->getListMeasures()){
                if(varMeasure->getType() == type_measure){
                    CVariableMeasure* measure = (CVariableMeasure*)varMeasure;
                    qDebug() << "--measure label : " << measure->getLabel();
                    qDebug() << "--measure value : " << measure->getMeasureVariable()->getLabel() << " " << measure->getMeasureVariable()->toFloat(); 
                    foreach(IVariable* var, measure->getListVariables()){
                        qDebug() << "---var label : " << var->getLabel();

                    }
                }else{
                    qDebug() << "Pas de type measure ???!! "<<varMeasure->getLabel();
                }

            }
        }
	}

}

CModelConfigFile::~CModelConfigFile()
{

}

QString CModelConfigFile::getLblAnalyser(const QLocale &local){
	QJsonObject jsonObject = m_jsonDoc->object();
	if(jsonObject[tr("FR_lbl_analyser")] == QJsonValue::Undefined)
        return tr("lbl_analyser not find see save.json file");
	else
		return jsonObject[tr("FR_lbl_analyser")].toString();
}

int CModelConfigFile::getNumberOfStream() const {
	QJsonObject jsonObject = m_jsonDoc->object();
    if(jsonObject[QStringLiteral("number_of_stream")] == QJsonValue::Undefined)
		return -1;
	else
        return jsonObject[QStringLiteral("number_of_stream")].toInt();
}
QMap<QString, ICycle*> CModelConfigFile::getMapCycle(){
	return m_mapCycles;
}

QList<ICycle *> CModelConfigFile::getListSequencesMesure(){
	return m_listSequences;
}
