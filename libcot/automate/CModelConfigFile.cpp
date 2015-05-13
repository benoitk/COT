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
#include "cotautomate_debug.h"
#include "qvariant.h"
#include "qmap.h"
#include "qfileinfo.h"
#include "cotautomate_debug.h"
//à suppirmer
#include "CVariableStream.h"
#include "CVariableMeasure.h"
//

CModelConfigFile::CModelConfigFile(QObject *parent)
	: QObject(parent)
{
	qCDebug(COTAUTOMATE_LOG) << "CModelConfigFile(QObject *parent)";
    QFile jsonFile(QString::fromLocal8Bit(COT_JSON_FILE));
	
    qCDebug(COTAUTOMATE_LOG) << "jsonFile.exists()" << jsonFile.exists();

    if (!jsonFile.open(QIODevice::ReadWrite)) {
        qCDebug(COTAUTOMATE_LOG) << "Couldn't open save file.";
    }
	QFileInfo fileInfo(jsonFile);
	qCDebug(COTAUTOMATE_LOG) << "fileInfo.path()" << fileInfo.absoluteFilePath();
	
    QByteArray jsonData = jsonFile.readAll();
	
	QJsonParseError * jsonError  = new QJsonParseError();
	m_jsonDoc = new QJsonDocument(QJsonDocument::fromJson(jsonData, jsonError));
	if(m_jsonDoc->isEmpty()){
		qCDebug(COTAUTOMATE_LOG) << "m_jsonDoc->isEmpty() " <<m_jsonDoc->isEmpty() ;
		qCDebug(COTAUTOMATE_LOG) << "jsonError " <<jsonError->errorString() ;
		qCDebug(COTAUTOMATE_LOG) << "jsonError offset" <<jsonError->offset ;
		qCDebug(COTAUTOMATE_LOG) << "jsonData " <<jsonData.mid(jsonError->offset, jsonError->offset+60) ;
	}

	QJsonObject jsonObjectAll = m_jsonDoc->object();
   
    //com_automate
     if(jsonObjectAll[QStringLiteral("com_automate")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"com_automate\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayComs = jsonObjectAll[QStringLiteral("com_automate")].toArray();
        foreach(QJsonValue jsonValueCom, jsonArrayComs){
            QVariantMap mapCom = jsonValueCom.toVariant().toMap();
            ICom* com = CComFactory::build(mapCom);
            if(com->getType() != type_com_unknow)
                CAutomate::getInstance()->addCom(com);
        }   
        qCDebug(COTAUTOMATE_LOG) << "mapComs " << CAutomate::getInstance()->getMapComs();
    }

    //extension
    if(jsonObjectAll[QStringLiteral("extensions")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"extensions\"] == QJsonValue::Undefined";
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
        qCDebug(COTAUTOMATE_LOG) << "mapExtCard " << CAutomate::getInstance()->getMapExtensions();
    }

    //Units
    if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"units\"] == QJsonValue::Undefined";
	}
	else {
        if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
		    qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"units\"] == QJsonValue::Undefined";
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
				            qCDebug(COTAUTOMATE_LOG) << "Converter null : map = " << mapConverter;

                        }
                    }
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Unit null : map = " << mapUnit ;

                }
            }
		}
    }

	//Variables
    if(jsonObjectAll[QStringLiteral("variables")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"variables\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayVariables = jsonObjectAll[QStringLiteral("variables")].toArray();
		foreach(QJsonValue jsonValueVariable, jsonArrayVariables){
			QVariantMap mapVariable = jsonValueVariable.toVariant().toMap();
			IVariable* var = CVariableFactory::build(mapVariable); 
			if(var)
                CAutomate::getInstance()->addVariable(mapVariable[QStringLiteral("name")].toString(),var);
			else 
				qCDebug(COTAUTOMATE_LOG) << "Variables null : map = " << mapVariable;
		}
	}

   

    //display
    if(jsonObjectAll[QStringLiteral("display")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"display\"] == QJsonValue::Undefined";
	}
	else {
       CDisplayConf* displayConf = new CDisplayConf(jsonObjectAll[QStringLiteral("display")].toArray(), CAutomate::getInstance());
       CAutomate::getInstance()->setDisplayConf(displayConf);
    }

	//bind variables
    if(jsonObjectAll[QStringLiteral("variables")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"variables\"] == QJsonValue::Undefined";
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
				qCDebug(COTAUTOMATE_LOG) << "Bind introuvable : map = " << mapBind;
		}
	}

	//Actions
    if(jsonObjectAll[QStringLiteral("actions")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"actions\"] == QJsonValue::Undefined";
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
				qCDebug(COTAUTOMATE_LOG) << "Action null : map = " << mapAction;
		}
        qCDebug(COTAUTOMATE_LOG) << "ACTIONS : " << m_mapActions;

	}

	//Cycles
	QJsonObject jsonObjectCycle = m_jsonDoc->object();
    if(jsonObjectCycle[QStringLiteral("cycles")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"cycles\"] == QJsonValue::Undefined";
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
				qCDebug(COTAUTOMATE_LOG) << "Cycle null : map = " << mapCycle;

            if(cycle)
            qCDebug(COTAUTOMATE_LOG) << "INFO CYCLE : " << cycle->getListSteps();
		}
        qCDebug(COTAUTOMATE_LOG) << "CYCLES : " << m_mapCycles;
	}

	//Séquenceur
    QJsonObject jsonObjectSequencer = m_jsonDoc->object();
    if(jsonObjectSequencer[QStringLiteral("scheduler")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"scheduler\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequencer[QStringLiteral("scheduler")].toArray();
		foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
			QVariantMap mapSequence = jsonValueSequence.toVariant().toMap();
            if(mapSequence[QStringLiteral("cycle")] != QStringLiteral(""))
                m_listSequences.append(m_mapCycles[mapSequence[QStringLiteral("cycle")].toString()]);
			else
				qCDebug(COTAUTOMATE_LOG) << "Sequence name cycle null : map = " << mapSequence;
		}
        qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << m_listSequences;

	}
	qCDebug(COTAUTOMATE_LOG) << "FIN CModelConfigFile(QObject *parent)";

     //Streams : 
     if(jsonObjectAll[QStringLiteral("streams")] == QJsonValue::Undefined){
		qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"streams\"] == QJsonValue::Undefined";
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
				qCDebug(COTAUTOMATE_LOG) << "Streams null : map = " << mapStream;
		}

        CAutomate* a = CAutomate::getInstance();
        foreach(IVariable* varStream, a->getMapStreams()){
            CVariableStream* stream = (CVariableStream*)varStream;
            qCDebug(COTAUTOMATE_LOG) << "-stream label : " << stream->getLabel(); 
            qCDebug(COTAUTOMATE_LOG) << "-stream active : " << stream->getActiveState()->getLabel() << " " << stream->getActiveState()->toBool(); 
            foreach(IVariable* varMeasure, stream->getListMeasures()){
                if(varMeasure->getType() == type_measure){
                    CVariableMeasure* measure = (CVariableMeasure*)varMeasure;
                    qCDebug(COTAUTOMATE_LOG) << "--measure label : " << measure->getLabel();
                    qCDebug(COTAUTOMATE_LOG) << "--measure value : " << measure->getMeasureVariable()->getLabel() << " " << measure->getMeasureVariable()->toFloat(); 
                    foreach(IVariable* var, measure->getListVariables()){
                        qCDebug(COTAUTOMATE_LOG) << "---var label : " << var->getLabel();

                    }
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Pas de type measure ???!! "<<varMeasure->getLabel();
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
