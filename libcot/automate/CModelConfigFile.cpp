#include "CModelConfigFile.h"

#include "IAction.h"
#include "ICycle.h"
#include "IConverter.h"
#include "ICom.h"
#include "ICommand.h"
#include "ccommandfactory.h"
#include "CComFactory.h"
#include "CConverterFactory.h"
#include "CCycleFactory.h"
#include "CActionFactory.h"
#include "CVariableFactory.h"
#include "CAutomate.h"
#include "CUnit.h"
#include "CDisplayConf.h"
#include "CModelExtensionCard.h"
#include "CScheduler.h"
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

#include <QApplication>
#include <QTranslator>

CModelConfigFile::CModelConfigFile(QObject *parent)
    : QObject(parent)
{
    qCDebug(COTAUTOMATE_LOG) << "CModelConfigFile(QObject *parent) thread " << this->thread();
    QFile jsonFile(QString::fromLocal8Bit(JSON_DIRECTORY "/save.json"));

    qCDebug(COTAUTOMATE_LOG) << "jsonFile.exists()" << jsonFile.exists();

    if (!jsonFile.open(QIODevice::ReadWrite)) {
        qCDebug(COTAUTOMATE_LOG) << "Couldn't open save file.";
    }
    QFileInfo fileInfo(jsonFile);
    qCDebug(COTAUTOMATE_LOG) << "fileInfo.path()" << fileInfo.absoluteFilePath();

    QByteArray jsonData = jsonFile.readAll();

    QJsonParseError * jsonError  = new QJsonParseError();
    m_jsonDoc = new QJsonDocument(QJsonDocument::fromJson(jsonData, jsonError));
    if(m_jsonDoc->isEmpty() || jsonError->error){
        qWarning() << "m_jsonDoc->isEmpty() " <<m_jsonDoc->isEmpty() ;
        qWarning() << "jsonError " <<jsonError->errorString() ;
        qWarning() << "jsonError offset" <<jsonError->offset ;
        qWarning() << "jsonData " <<jsonData.mid(jsonError->offset, jsonError->offset+60) ;
    }

    QJsonObject jsonObjectAll = m_jsonDoc->object();

    CAutomate *automate = CAutomate::getInstance();


    //lang
    if(jsonObjectAll[QStringLiteral("lang")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"lang\"] == QJsonValue::Undefined";
    }
    else{
        QTranslator* qtTranslator = new QTranslator;
        QString lang = jsonObjectAll[QStringLiteral("lang")].toString();
        automate->setLang(lang);
        if(qtTranslator->load(QString(":/"+lang+".qm")))
            qDebug() << "Fichier "+ QString(":/"+lang+".qm") +" chargé" ;
        else
            qDebug() << "Pas de fichier de trad chargé" ;
        if(!QApplication::instance()->installTranslator(qtTranslator)){
            qDebug() << "Trad non installé";
        }

    }
        //debug
    if(jsonObjectAll[QStringLiteral("debug")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"extensions\"] == QJsonValue::Undefined";
    }
    else{
        automate->setDebug(jsonObjectAll[QStringLiteral("debug")].toBool());
    }

    //slave com
    if(jsonObjectAll[QStringLiteral("slave_coms_available")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"slave_coms_available\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArrayVariables = jsonObjectAll[QStringLiteral("slave_coms_available")].toArray();
        foreach(QJsonValue jsonValueVariable, jsonArrayVariables){
            QVariantMap mapVariable = jsonValueVariable.toVariant().toMap();
            ICom* var = CComFactory::build(mapVariable);
            if(var)
                automate->addCom(var);
            else
                qCDebug(COTAUTOMATE_LOG) << "slave_coms_available null : map = " << mapVariable;
        }
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
                automate->addExtensionCard(mapExt.value(QStringLiteral("name")).toString(), ext);
            }
        }
        qCDebug(COTAUTOMATE_LOG) << "mapExtCard " << automate->getMapExtensions();
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
            foreach(QJsonValue jsonValueUnit, jsonArrayUnits){
                QVariantMap mapUnit = jsonValueUnit.toVariant().toMap();
                if(!mapUnit[QStringLiteral("name")].isNull()) {
                    CUnit* unit = new CUnit(mapUnit[QStringLiteral("name")].toString()
                                          , mapUnit[tr("en_US")].toString());
                    automate->addUnit(unit);
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Unit null : map = " << mapUnit ;

                }
            }
        }
    }
    automate->addUnit(new CUnit(QStringLiteral("no_unit"), QStringLiteral("")));

    //Unit converters
    if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"units_convertion\"] == QJsonValue::Undefined";
    }
    else {
        if(jsonObjectAll[QStringLiteral("units")] == QJsonValue::Undefined ){
            qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"units_convertion\"] == QJsonValue::Undefined";
        }
        else {
            QJsonArray jsonArrayConverters = jsonObjectAll[QStringLiteral("units_convertion")].toArray();
            foreach(QJsonValue jsonValueConverter, jsonArrayConverters){
                QVariantMap mapConverter = jsonValueConverter.toVariant().toMap();
                CUnit* unit = automate->getUnit(mapConverter[QStringLiteral("source")].toString());
                if(unit->getName() ==  mapConverter[QStringLiteral("source")].toString()) {
                    IConverter* converter = CConverterFactory::build(mapConverter);
                    unit->addConverter(mapConverter[QStringLiteral("target")].toString(),converter);
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Unknow unit : map = " << mapConverter;

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
            if(var){
                automate->addVariable(mapVariable[QStringLiteral("name")].toString(),var);
                var->initComs();
            }
            else
                qCDebug(COTAUTOMATE_LOG) << "Variables null : map = " << mapVariable;
        }
    }

    //bind variables
    if(jsonObjectAll[QStringLiteral("variables")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"variables\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArrayBinds = jsonObjectAll[QStringLiteral("binds")].toArray();
        foreach(QJsonValue jsonValueBind, jsonArrayBinds){
            QVariantMap mapBind = jsonValueBind.toVariant().toMap();
            IVariable* var = automate->getVariable(mapBind[QStringLiteral("source")].toString());
            IVariable* var_binded = automate->getVariable(mapBind[QStringLiteral("target")].toString());
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
            IAction* action = CActionFactory::build(mapAction, automate);
            if(action){
                m_mapActions.insert(action->getName(),action);
                automate->addAction(action);
            }else
                qCDebug(COTAUTOMATE_LOG) << "Action null : map = " << mapAction;
        }
        //qCDebug(COTAUTOMATE_LOG) << "ACTIONS : " << m_mapActions;

    }

    //Commands
    if(jsonObjectAll[QStringLiteral("commands")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"commands\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArrayCommands = jsonObjectAll[QStringLiteral("commands")].toArray();

        foreach(QJsonValue jsonValueCmd, jsonArrayCommands){
            QVariantMap mapCmd = jsonValueCmd.toVariant().toMap();
            ICommand* command = CCommandFactory::build(mapCmd, automate);
            if(command && command->getName() == QStringLiteral("cmd_play_stop_cycle")){
                automate->setCommandPlayStop(command);
            }else if(command && command->getName() == QStringLiteral("cmd_stop_end_cycle")){
                automate->setCommandStopEndCycle(command);
            }else if(command && command->getName() == QStringLiteral("cmd_next_cycle")){
                automate->setCommandNextCycle(command);
            }else
                qCDebug(COTAUTOMATE_LOG) << "ICommand null : map = " << mapCmd;
        }
        //qCDebug(COTAUTOMATE_LOG) << "ACTIONS : " << m_mapActions;

    }

    //display
    if(jsonObjectAll[QStringLiteral("display")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"display\"] == QJsonValue::Undefined";
    }
    else {
       CDisplayConf* displayConf = new CDisplayConf(jsonObjectAll[QStringLiteral("display")].toArray(), automate);
       automate->setDisplayConf(displayConf);
    }

    //Cycles
    QJsonObject jsonObjectCycle = m_jsonDoc->object();
    if(jsonObjectCycle[QStringLiteral("cycles")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"cycles\"] == QJsonValue::Undefined";
    }
    else {

        QJsonArray jsonArrayCycles = jsonObjectCycle[QStringLiteral("cycles")].toArray();
        foreach(QJsonValue jsonValueCycle, jsonArrayCycles){
            QVariantMap mapCycle = jsonValueCycle.toVariant().toMap();
            ICycle* cycle = CCycleFactory::build(mapCycle, automate->getScheduler());
            if(cycle) {
                m_mapCycles.insert(cycle->getName(),cycle);
                automate->addCycle(cycle);
            }
            else
                qCDebug(COTAUTOMATE_LOG) << "Cycle null : map = " << mapCycle;

            if(cycle)
            qCDebug(COTAUTOMATE_LOG) << "INFO CYCLE : " << cycle->getListSteps();
        }
        //qCDebug(COTAUTOMATE_LOG) << "CYCLES : " << m_mapCycles;
    }

    //Séquenceur mesure
    QJsonObject jsonObjectSequencer = m_jsonDoc->object();
    if(jsonObjectSequencer[QStringLiteral("scheduler_measure")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"scheduler_measure\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequencer[QStringLiteral("scheduler_measure")].toArray();
        foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
            QString sequenceName = jsonValueSequence.toVariant().toString();
            if(sequenceName != QStringLiteral(""))
                automate->getScheduler()->addCycleMeasure(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence name cycle null : map = " << sequenceName;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER MEASURE : " << automate->getSequencer()->getListSequenceCyclesMesures();

    }

    //Séquenceur autonome
    QJsonObject jsonObjectSequencerAutonome = m_jsonDoc->object();
    if(jsonObjectSequencerAutonome[QStringLiteral("scheduler_autonome")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"scheduler_autonome\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequencerAutonome[QStringLiteral("scheduler_autonome")].toArray();
        foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
            QString sequenceName = jsonValueSequence.toVariant().toString();
            if(sequenceName != QStringLiteral(""))
                automate->getScheduler()->addCycleAutonome(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence name cycle null : map = " << sequenceName;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << automate->getSequencer()->getListSequenceCyclesAutonomes();

    }

    //Liste cycles de maintenance
    QJsonObject jsonObjectSequencerMaintenance = m_jsonDoc->object();
    if(jsonObjectSequencerMaintenance[QStringLiteral("list_cycles_maintenances")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"list_cycles_maintenances\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArraySequenceur = jsonObjectSequencerMaintenance[QStringLiteral("list_cycles_maintenances")].toArray();
        foreach(QJsonValue jsonValueSequence, jsonArraySequenceur){
            QString sequenceName = jsonValueSequence.toVariant().toString();
            if(sequenceName != QStringLiteral(""))
                automate->getScheduler()->addCycleMaintenance(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "name cycle null : map = " << sequenceName;
        }
        qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << automate->getScheduler()->getListCyclesMaintenances();

    }

    //Séquenceur maintenance
    QJsonObject jsonObjectSequencerMaintenanceAuto = m_jsonDoc->object();
    if(jsonObjectSequencerMaintenanceAuto[QStringLiteral("scheduler_maintenances")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"scheduler_maintenances\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArraySeqeuceur = jsonObjectSequencerAutonome[QStringLiteral("scheduler_maintenances")].toArray();
        foreach(QJsonValue jsonValueSequence, jsonArraySeqeuceur){
            QVariantMap sequenceMap = jsonValueSequence.toVariant().toMap();
            if(!sequenceMap.isEmpty())
                automate->getScheduler()
                        ->addCycleMaintenanceAuto(CSequenceMaintenanceFactory::build(sequenceMap, CScheduler::getInstance()));
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence maintenance auto null : map = " << sequenceMap;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << automate->getSequencer()->getListSequenceCyclesAutonomes();

    }

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
                automate->addStream(static_cast<CVariableStream *>(var));
            else
                qCDebug(COTAUTOMATE_LOG) << "Streams null : map = " << mapStream;
        }

        foreach(CVariableStream* stream, automate->getListStreams()){
            qCDebug(COTAUTOMATE_LOG) << "-stream label : " << stream->getLabel();
            qCDebug(COTAUTOMATE_LOG) << "-stream active : " << stream->getActiveState()->getLabel() << " " << stream->getActiveState()->toBool();
            foreach(IVariable* varMeasure, stream->getListMeasures()){
                if(varMeasure->getType() == e_type_measure){
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

     //Logs
     {
     QJsonObject jsonObjectLogs = m_jsonDoc->object();
     if(jsonObjectLogs[QStringLiteral("logs")] == QJsonValue::Undefined){
         qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"logs\"] == QJsonValue::Undefined";
     }
     else {
         QJsonArray jsonArrayLogs = jsonObjectLogs[QStringLiteral("logs")].toArray();
         foreach(QJsonValue jsonVarName, jsonArrayLogs){
             QString varName = jsonVarName.toVariant().toString();
             if(varName != QStringLiteral(""))
                 automate->addLoggedVariable(varName);
             else
                 qCDebug(COTAUTOMATE_LOG) << "Logs null : map = " << varName;
         }
     }
     }
     //Logs debug
     {
     QJsonObject jsonObjectLogs = m_jsonDoc->object();
     if(jsonObjectLogs[QStringLiteral("logs_debug")] == QJsonValue::Undefined){
         qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"logs_debug\"] == QJsonValue::Undefined";
     }
     else {
         QJsonArray jsonArrayLogs = jsonObjectLogs[QStringLiteral("logs_debug")].toArray();
         foreach(QJsonValue jsonVarName, jsonArrayLogs){
             QString varName = jsonVarName.toVariant().toString();
             if(varName != QStringLiteral(""))
                 automate->addLoggedVariable(varName, true);
             else
                 qCDebug(COTAUTOMATE_LOG) << "Logs null : map = " << varName;
         }
     }
    }
    qCDebug(COTAUTOMATE_LOG) << "FIN CModelConfigFile(QObject *parent)";
}
void CModelConfigFile::saveJson(const QVariantMap& arg_mapSerialized){

}

CModelConfigFile::~CModelConfigFile()
{

}

QString CModelConfigFile::getLabelAnalyser(const QLocale &local){
    QJsonObject jsonObject = m_jsonDoc->object();
    if(jsonObject[tr("en_US")] == QJsonValue::Undefined)
        return tr("lbl_analyser not find see save.json file");
    else
        return jsonObject[tr("l_analyser")].toString();
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
