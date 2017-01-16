#include "CConfigFileHandler.h"

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
#include "CState.h"

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
#include "CPCWindow.h"
#include "CMessageBox.h"

#include <QApplication>
#include <QTranslator>

CConfigFileHandler::CConfigFileHandler(CAutomate *arg_automate, CScheduler* scheduler)
    : QObject(arg_automate), m_scheduler(scheduler), m_automate(arg_automate)
{
}

bool CConfigFileHandler::checkSyntaxeError(const QString & arg_filePath){
    QString filePath;
    if(arg_filePath.isEmpty())
        filePath = JSON_DIRECTORY "save.json";
    else
        filePath = arg_filePath;
    QFile jsonFile(filePath);
    if(!jsonFile.exists()){
        qDebug(COTAUTOMATE_LOG) << "CConfigFileHandler::checkSyntaxeError File " << filePath << " don't exist";
        return false;
    }
    if (!jsonFile.open(QIODevice::ReadWrite)) {
        qCDebug(COTAUTOMATE_LOG) << "Couldn't open save file " << filePath;
        return false;
    }
    QFileInfo fileInfo(jsonFile);
    qCDebug(COTAUTOMATE_LOG) << "fileInfo.path()" << fileInfo.absoluteFilePath();

    QByteArray jsonData = jsonFile.readAll();

    QJsonParseError * jsonError  = new QJsonParseError();
    m_jsonDoc = new QJsonDocument(QJsonDocument::fromJson(jsonData, jsonError));
    if( jsonError->error){
        qWarning() << "jsonError " <<jsonError->errorString() ;
        qWarning() << "jsonError offset" <<jsonError->offset ;
        qWarning() << "jsonData " <<jsonData.mid(jsonError->offset,100) ;
        CMessageBox *msg = new CMessageBox(tr("Syntax error on configuration file after :") +"\n" + jsonData.mid(jsonError->offset-80,79));
        msg->exec();
        delete msg;
        return false;
    }

    return true;
}

bool CConfigFileHandler::loadConf(){
    qCDebug(COTAUTOMATE_LOG) << "CConfigFileHandler(QObject *parent) thread " << this->thread();
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

    //lang
    if(jsonObjectAll[QStringLiteral("lang")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"lang\"] == QJsonValue::Undefined";
    }
    else{
        QTranslator* qtTranslator = new QTranslator;
        QString lang = jsonObjectAll[QStringLiteral("lang")].toString();
        m_automate->setLang(lang);
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
        m_automate->setDebug(jsonObjectAll[QStringLiteral("debug")].toBool());
    }

    //slave com
    if(jsonObjectAll[QStringLiteral("slave_coms_available")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"slave_coms_available\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArrayVariables = jsonObjectAll[QStringLiteral("slave_coms_available")].toArray();
        foreach(QJsonValue jsonValueVariable, jsonArrayVariables){
            QVariantMap mapVariable = jsonValueVariable.toVariant().toMap();
            qDebug() << QThread::currentThreadId();
            ICom* com = CComFactory::build(mapVariable);
            if(com)
                m_automate->addCom(com);
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
                m_automate->addExtensionCard(mapExt.value(QStringLiteral("name")).toString(), ext);
            }
        }
        qCDebug(COTAUTOMATE_LOG) << "mapExtCard " << m_automate->getMapExtensions();
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
                    m_automate->addUnit(unit);
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Unit null : map = " << mapUnit ;

                }
            }
        }
    }
    m_automate->addUnit(new CUnit(QStringLiteral("no_unit"), QStringLiteral("")));

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
                CUnit* unit = m_automate->getUnit(mapConverter[QStringLiteral("source")].toString());
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
            IVariable* var = CVariableFactory::build(m_automate, m_automate, mapVariable);
            var->initComs();
            if(var){
                m_automate->addVariable(mapVariable[QStringLiteral("name")].toString(),var);
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
            IVariable* var = m_automate->getVariable(mapBind[QStringLiteral("source")].toString());
            IVariable* var_binded = m_automate->getVariable(mapBind[QStringLiteral("target")].toString());
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
            IAction* action = CActionFactory::build(mapAction, m_automate);
            if(action){
                m_mapActions.insert(action->getName(),action);
                m_automate->addAction(action);
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
            ICommand* command = CCommandFactory::build(mapCmd, m_automate);
            if(command && command->getName() == QStringLiteral("cmd_play_stop_cycle")){
                m_automate->setCommandPlayStop(command);
            }else if(command && command->getName() == QStringLiteral("cmd_stop_end_cycle")){
                m_automate->setCommandStopEndCycle(command);
            }else if(command && command->getName() == QStringLiteral("cmd_next_cycle")){
                m_automate->setCommandNextCycle(command);
            }else
                qCDebug(COTAUTOMATE_LOG) << "ICommand null : map = " << mapCmd;
        }
        //qCDebug(COTAUTOMATE_LOG) << "ACTIONS : " << m_mapActions;

    }

//    //states
    if(jsonObjectAll[QStringLiteral("states")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"states\"] == QJsonValue::Undefined";
    }
    else {
        QJsonArray jsonArraystates = jsonObjectAll[QStringLiteral("states")].toArray();

        foreach(QJsonValue jsonValueState, jsonArraystates){
            QVariantMap mapState = jsonValueState.toVariant().toMap();

            CState* state = Q_NULLPTR;
            if(mapState.value("name").toString() == QStringLiteral("state_in_maintenance")){
                state = m_automate->getStateInMaintenance();
            }else  if(mapState.value("name").toString() == QStringLiteral("state_cycle_running")){
                state = m_automate->getStateIsRunning();
            }else  if(mapState.value("name").toString() == QStringLiteral("state_cycle_paused")){
                state = m_automate->getStateCurrentCycleIsPaused();
            }else  if(mapState.value("name").toString() == QStringLiteral("state_cycle_auto_running")){
                state = m_automate->getStateCycleAutoRunning();
            }else  if(mapState.value("name").toString() == QStringLiteral("state_cycle_running_will_stop_end_cycle")){
                state = m_automate->getStateWillStopEndCycle();
            }
            if(state != Q_NULLPTR){
                state->setState(mapState.value("default_state").toBool());
                QVariantList listOutputVariables = mapState.value("output_variables").toList();
                foreach(QVariant var, listOutputVariables){
                    state->addOutputVariable(m_automate->getVariable(var.toString()));
                }
            }
        }
        //qCDebug(COTAUTOMATE_LOG) << "ACTIONS : " << m_mapActions;

    }

    //display
    if(jsonObjectAll[QStringLiteral("display")] == QJsonValue::Undefined){
        qCDebug(COTAUTOMATE_LOG) << "jsonObject[\"display\"] == QJsonValue::Undefined";
    }
    else {
       CDisplayConf* displayConf = new CDisplayConf(jsonObjectAll[QStringLiteral("display")].toArray(), m_automate);
       m_automate->setDisplayConf(displayConf);
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
            ICycle* cycle = CCycleFactory::build(mapCycle, m_automate->getScheduler());
            if(cycle) {
                m_mapCycles.insert(cycle->getName(),cycle);
                m_automate->addCycle(cycle);
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
                m_automate->getScheduler()->addCycleMeasure(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence name cycle null : map = " << sequenceName;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER MEASURE : " << m_automate->getSequencer()->getListSequenceCyclesMesures();

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
                m_automate->getScheduler()->addCycleAutonome(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence name cycle null : map = " << sequenceName;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << m_automate->getSequencer()->getListSequenceCyclesAutonomes();

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
                m_automate->getScheduler()->addCycleMaintenance(m_mapCycles[sequenceName]);
            else
                qCDebug(COTAUTOMATE_LOG) << "name cycle null : map = " << sequenceName;
        }
        qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << m_automate->getScheduler()->getListCyclesMaintenances();

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
                m_automate->getScheduler()
                        ->addCycleMaintenanceAuto(CSequenceMaintenanceFactory::build(sequenceMap, m_scheduler));
            else
                qCDebug(COTAUTOMATE_LOG) << "Sequence maintenance auto null : map = " << sequenceMap;
        }
        //qCDebug(COTAUTOMATE_LOG) << "SEQUENCER : " << m_automate->getSequencer()->getListSequenceCyclesAutonomes();

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
            IVariable* var = CVariableFactory::build(m_automate, m_automate, mapStream);
            if(var)
                m_automate->addStream(static_cast<CVariableStream *>(var));
            else
                qCDebug(COTAUTOMATE_LOG) << "Streams null : map = " << mapStream;
        }

        foreach(CVariableStream* stream, m_automate->getListStreams()){
            qCDebug(COTAUTOMATE_LOG) << "-stream label : " << stream->getLabel();
            qCDebug(COTAUTOMATE_LOG) << "-stream active : " << stream->getActiveState()->getLabel() << " " << stream->getActiveState()->toBool();
            foreach(IVariable* varMeasure, stream->getListMeasures()){
                if(varMeasure->getType() == e_type_measure){
                    CVariableMeasure* measure = static_cast<CVariableMeasure*>(varMeasure);
                    qCDebug(COTAUTOMATE_LOG) << "--measure label : " << measure->getLabel();
                    qCDebug(COTAUTOMATE_LOG) << "--measure value : " << measure->getMeasureVariable()->getLabel() << " " << measure->getMeasureVariable()->toFloat();
                    foreach(IVariable* var, measure->getListVariables()){
                        qCDebug(COTAUTOMATE_LOG) << "---var label : " << var->getLabel();

                    }
                }else{
                    qCDebug(COTAUTOMATE_LOG) << "Pas de type measure ? "<<varMeasure->getLabel();
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
                 m_automate->addLoggedVariable(varName);
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
                 m_automate->addLoggedVariable(varName, true);
             else
                 qCDebug(COTAUTOMATE_LOG) << "Logs null : map = " << varName;
         }
     }
    }
    qCDebug(COTAUTOMATE_LOG) << "FIN CConfigFileHandler(QObject *parent)";
    return true;
}
void CConfigFileHandler::saveJson(const QVariantMap& arg_mapSerialized){

}

CConfigFileHandler::~CConfigFileHandler()
{

}

QString CConfigFileHandler::getLabelAnalyser(const QLocale &local){
    QJsonObject jsonObject = m_jsonDoc->object();
    if(jsonObject[tr("en_US")] == QJsonValue::Undefined)
        return tr("lbl_analyser not find see save.json file");
    else
        return jsonObject[tr("l_analyser")].toString();
}

int CConfigFileHandler::getNumberOfStream() const {
    QJsonObject jsonObject = m_jsonDoc->object();
    if(jsonObject[QStringLiteral("number_of_stream")] == QJsonValue::Undefined)
        return -1;
    else
        return jsonObject[QStringLiteral("number_of_stream")].toInt();
}
QMap<QString, ICycle*> CConfigFileHandler::getMapCycle(){
    return m_mapCycles;
}

QList<ICycle *> CConfigFileHandler::getListSequencesMesure(){
    return m_listSequences;
}
