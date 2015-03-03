#include "CModelConfigFile.h"

#include "IAction.h"
#include "ICycle.h"
#include "CCycleFactory.h"
#include "CActionFactory.h"
#include "CVariableFactory.h"
#include "CAutomate.h"

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
	QFile jsonFile("save.json");
	
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

	QJsonObject jsonObjectAction = m_jsonDoc->object();

	//Variables
	if(jsonObjectAction["variables"] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"variables\"] == QJsonValue::Undefined";
	}
	else {
		QJsonArray jsonArrayVariables = jsonObjectAction["variables"].toArray();
		foreach(QJsonValue jsonValueVariable, jsonArrayVariables){
			QVariantMap mapVariable = jsonValueVariable.toVariant().toMap();
			IVariable* var = CVariableFactory::build(mapVariable); 
			if(var)
				CAutomate::getInstance()->addVariable(mapVariable["name"].toString(),var);
			else 
				qDebug() << "Variables null : map = " << mapVariable;
		}
	}
	//bind variables
	if(jsonObjectAction["variables"] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"variables\"] == QJsonValue::Undefined";
	}
	else {
		QJsonArray jsonArrayBinds = jsonObjectAction["binds"].toArray();
		foreach(QJsonValue jsonValueBind, jsonArrayBinds){
			QVariantMap mapBind = jsonValueBind.toVariant().toMap();
			IVariable* var = CAutomate::getInstance()->getVariable(mapBind["variable_origin_name"].toString());
			IVariable* var_binded = CAutomate::getInstance()->getVariable(mapBind["variable_destination_name"].toString());
			if(var && var_binded)
				var->addBind(var_binded);
			else 
				qDebug() << "Bind introuvable : map = " << mapBind;
		}
	}

	//Actions
	if(jsonObjectAction["actions"] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"actions\"] == QJsonValue::Undefined";
	}
	else {
		QJsonArray jsonArrayActions = jsonObjectAction["actions"].toArray();
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
	if(jsonObjectCycle["cycles"] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"cycles\"] == QJsonValue::Undefined";
	}
	else {
		QJsonArray jsonArrayCycles = jsonObjectCycle["cycles"].toArray();
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
	if(jsonObjectSequenceur["sequenceur_measure"] == QJsonValue::Undefined){
		qDebug() << "jsonObject[\"sequenceur_measure\"] == QJsonValue::Undefined";
	}
	else {
		QJsonArray jsonArraySeqeuceur = jsonObjectSequenceur["sequenceur_measure"].toArray();
		foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
			QVariantMap mapSequence = jsonValueSequence.toVariant().toMap();
			if(mapSequence["name_cycle"] != "")
				m_listSequences.append(m_mapCycles[mapSequence["name_cycle"].toString()]);
			else
				qDebug() << "Sequence name cycle null : map = " << mapSequence;
		}
	}
	qDebug() << "FIN CModelConfigFile(QObject *parent)";

}

CModelConfigFile::~CModelConfigFile()
{

}

QString CModelConfigFile::getLblAnalyser(QLocale local){
	QJsonObject jsonObject = m_jsonDoc->object();
	if(jsonObject[tr("FR_lbl_analyser")] == QJsonValue::Undefined)
		return QString(tr("lbl_analyser not find see save.json file"));
	else
		return jsonObject[tr("FR_lbl_analyser")].toString();
}

int CModelConfigFile::getNumberOfStream(){
	QJsonObject jsonObject = m_jsonDoc->object();
	if(jsonObject["number_of_stream"] == QJsonValue::Undefined)
		return -1;
	else
		return jsonObject["number_of_stream"].toInt();
}
QMap<QString, ICycle*> CModelConfigFile::getMapCycle(){
	return m_mapCycles;
}

QList<ICycle *> CModelConfigFile::getListSequenceurMesure(){
	return m_listSequences;
}
