#include "CModelConfigFile.h"

#include "IAction.h"
#include "ICycle.h"
#include "CCycleFactory.h"
#include "CActionFactory.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CUnit.h"

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
   
    //Units
    if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"units\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayUnits = jsonObjectAll[QStringLiteral("units")].toArray();
		foreach(QJsonValue jsonValueUnit, jsonArrayUnits){
			QVariantMap mapUnit = jsonValueUnit.toVariant().toMap();
            if(mapUnit[QStringLiteral("name")].isNull()) {
                CUnit* unit = new CUnit(mapUnit[QStringLiteral("name")].toString()
                                      , mapUnit[tr("fr_FR")].toString());
                CAutomate::getInstance()->addUnit(unit);
            }else{
				qDebug() << "Unit null : map = " << mapUnit;

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
			if(action)
				m_mapActions.insert(action->getName(),action);
			else 
				qDebug() << "Action null : map = " << mapAction;
		}
	}

	//Cycles
	QJsonObject jsonObjectCycle = m_jsonDoc->object();
    if(jsonObjectCycle[QStringLiteral("cycles")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"cycles\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArrayCycles = jsonObjectCycle[QStringLiteral("cycles")].toArray();
		foreach(QJsonValue jsonValueCycle, jsonArrayCycles){
			QVariantMap mapCycle = jsonValueCycle.toVariant().toMap();
			ICycle* cycle = CCycleFactory::build(mapCycle, m_mapActions); 
			if(cycle)
				m_mapCycles.insert(cycle->getName(),cycle);
			else
				qDebug() << "Cycle null : map = " << mapCycle;
		}
	}

	//Séquenceur
	QJsonObject jsonObjectSequenceur = m_jsonDoc->object();
    if(jsonObjectSequenceur[QStringLiteral("sequenceur_measure")] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"sequenceur_measure\"] == QJsonValue::Undefined";
	}
	else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequenceur[QStringLiteral("sequenceur_measure")].toArray();
		foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
			QVariantMap mapSequence = jsonValueSequence.toVariant().toMap();
            if(mapSequence[QStringLiteral("name_cycle")] != QStringLiteral(""))
                m_listSequences.append(m_mapCycles[mapSequence[QStringLiteral("name_cycle")].toString()]);
			else
				qDebug() << "Sequence name cycle null : map = " << mapSequence;
		}
	}
	qDebug() << "FIN CModelConfigFile(QObject *parent)";

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
