#ifndef CAUTOMATE_H
#define CAUTOMATE_H

#include "IComObserver.h"


#include "CVariableFloat.h"
#include "CVariableBool.h"
#include "CVariableString.h"
#include "CVariableInt.h"
#include "CVariableInputBool.h"
#include "CVariableInputFloat.h"
#include "CVariableInputInt.h"
#include "CVariableOutputBool.h"
#include "CVariableOutputFloat.h"
#include "CVariableOutputInt.h"
#include "CState.h"

#include <QObject>
#include <QStringList>
#include <QDateTime>
#include "qmap.h"
#include "qmutex.h"

//Automade de gestion des cycles
class ICycle;
class ICommand;
class CControlerCycle;
class CScheduler;
class IVariable;
class CVariableAlarm;
class CModelExtensionCard;
class IAction;
class CUnit;
class CDisplayConf;
class IOrgan;
class CVariableStream;
class CThreadDiag;
class CVariableMeasure;
class CAutomate : public QObject, IComObserver
{
    Q_OBJECT

public:
    bool isCycleStoppeByAlarm();
    void enterMaintenanceMode();
    void exitMaintenanceMode();

    //use for API
    QMap<QString, CModelExtensionCard*> getMapExtensions();
    QMap<QString, ICom*> getMapComs();
    QList<ICycle*> getListCycles(int cycleType = 0);
    QList<IAction*> getListActions();//en redondance avec getMapActions pour ne pas refaire niveau IHM
    QMap<QString, IAction*> getMapActions();
    QList<CUnit*> getListUnits();
    QMap<QString, IVariable*> getMapVariables();
    QList<CVariableStream*> getListStreams();
    void setMapVariables(QMap<QString, IVariable*>);
    CDisplayConf* getDisplayConf()const;
    void acquitAlarms();
    // Those members are called by configurator once the user clicks Ok
    void informAboutCycleChanges(ICycle *cycle, const QVariantMap &oldData);
    void informAboutVariableChanges(IVariable *variable, const QVariantMap &oldData);

    void requestPlayScheduler();
    bool requestPlayMaintenance(const QString&);
    void requestStopScheduler();
    void requestStopEndCycleScheduler();
    void requestCancelStopEndCycleScheduler();
    void pauseScheduler();
    void requestPlayNextSequenceMesure();

    void changeCycleStream(ICycle*, CVariableStream* arg_dest_stream);
    void changeVariableStream(IVariable*, CVariableStream* arg_dest_stream);
    CVariableStream* getCycleStream(ICycle*) const;
    CVariableStream* getVariableStream(IVariable*) const;

    CVariableMeasure* getVariableMeasure(IVariable*) const;
    void changeVariableMeasure(IVariable*, CVariableMeasure* arg_dest_measure);
    CVariableStream *getMeasureStream(CVariableMeasure *measure) const;
    //FIN API

    CState* getStateInMaintenance();
    CState* getStateIsRunning();
    CState* getStateCurrentCycleIsPaused();
    CState* getStateWillStopEndCycle();
    CState* getStateCycleAutoRunning();

    void setStateWillStopEndCycle(bool);
    void setStateCycleAutoRunning(bool);
    void setStateIsRunning(bool);
    void setStateCurrentCycleIsPaused(bool);

    static QString formatHistoryEntry(const QString &name, const QDateTime &dateTime);

    enum eStateStream{STREAM_DEFAULT, WATER_DEFAULT, ACTIVE, INACTIVE};
    static CAutomate* getInstance();

    void setDisplayConf(CDisplayConf*);

    void addCycle(ICycle*);

    ICycle *getCycle(const QString &name, int type = 0) const;
    CUnit *getUnit(const QString &name) const;
    IOrgan *getOrgan(const QString &name) const;
    CVariableStream *getStream(const QString &name) const;
    CVariableMeasure *getMeasure(const QString &name) const;
    ICom* getCom(const QString &arg_name);
    IAction* getAction(const QString &arg_name);

    IVariable* getVariable(const QString&);
    QList<IVariable *> getVariables(const QStringList&);
    void addVariable(const QString&, IVariable*);
    void addStream(CVariableStream*, bool emitSignalOnAdd = false);
    void addUnit(CUnit*);
    void addCom(ICom*);
    void addAction(IAction*, bool emitSignal = false);
    void delAction(IAction*);
    void delAction(const QString&);
    void delVariable(IVariable *ivar);

    //commandes
    void setCommandPlayStop(ICommand*);
    void setCommandStopEndCycle(ICommand*);
    void setCommandNextCycle(ICommand*);

    ICommand* getCommandPlayStop();
    ICommand* getCommandStopEndCycle();
    ICommand* getCommandNextCycle();

    CModelExtensionCard* getExtensionCard(const QString&);
    void addExtensionCard(const QString&, CModelExtensionCard*);

    void delCycle(ICycle *cycle);
    void delStream(CVariableStream *ivar);

    CScheduler* getScheduler()const;

    //IComObserver
    IVariable* getVariableByAddr(const QString &addr_var)const Q_DECL_OVERRIDE;
    void setCom(ICom*) Q_DECL_OVERRIDE;

    void addVariableToMappingCom(IVariable*);

    void initConfig();
    void quit();
    void setLang(const QString&);
    void addLoggedVariable(const QString& arg_varName, bool arg_debug=false);

    bool isCyclesRunning();
    bool isLocalControlForced();
    IVariable* getLocalControlForced();

public slots:
    void slotSerializeAndSave();
    void slotResetCommands();
    void slotClock();
    void slotStartAutomate();
    void slotTabChanged(int tab_index);
    void slotLogVariable(IVariable* arg_var);
    void slotLogVariable();
    void slotNewAlarm(CVariableAlarm*);
    void slotAcquitedAlarm(CVariableAlarm*);
    void slotStillInAlarm(CVariableAlarm*);

    void setDebug(bool arg_debug);
signals:
    void signalRunCycle(int);
    void signalVariableChanged(const QString &name, const QDateTime &dateTime);
    // When internal state of a general cycle changed
    void signalCycleChanged(const QString &name);
    // When internal state of the current running maintenance cycle changed
    void signalCurrentMaintenanceCycleChanged(const QString &name);
    //Signal to update all data on the graphic
    void signalUpdatePlotting();



    //desc : Pas en cours changé
    //entrées : pas en cours; label du pas
    void signalUpdateCurrentStep(float, const QString &);
    void signalUpdateNumStep(float);
    void signalUpdateCurrentAction(const QString &);
    //desc : Nombre total de pas changé
    //entrées : Nombre de pas total
    void signalUpdateCountStep(int);
    //desc : Voie en court changé
    //entrées : numéro, Label voie
    void signalUpdateCurrentStream(int, const QString &);
    //desc : Nombre total de voie changée
    //entrées : Nombre de voie total
    void signalUpdateCountStream(int);
    //desc : Statue de voie changée : Active, en défeau d'eau...
    //entrées : enum de l'état de la voie
    void signalUpdateStateStream(const QString& arg_streamName, CAutomate::eStateStream);
    //desc : Valeur des variables de mesures affichable sur l'écran principale  (JSon : champ "streams->variables->type = measure)
    //entrées : identifiant et valeur de la variable de mesure,
    void signalUpdateMeasureValues(int, const QVariant &);
    //desc : Label et unité des variables de mesures affichable sur l'écran principale
    //entrées : identifiant, label et unité de la variable
    void signalUpdateMeasureLabels(int, const QString &);

    void signalNewAlarm(const QString&);
    void signalAquitAllAlarm();
    void signalRemoveAlarm(const QString&);

    //1 signal par section du json, dès qu'une valeur est modifié
    void signalNetworkUpdated();
    void signalComAutomateUpdated();
    void signalExtensionsUpdated();
    void signalUnitsUpdated(); //et Units_convertion
    void signalVariablesUpdated();
    void signalVariableUpdated(const QString &name);
    void signalDisplayUpdated();
    void signalBindsUpdated();
    void signalActionsUpdated();
    void signalCyclesUpdated();
    void signalSchedulerUpdated();
    void signalStreamsUpdated();


    //signals de mise à jours des états de l'automate TODO : virer l'enum stateAutomate
    void signalStateRunning(bool);
    void signalStateRunningWillStopEndCycle(bool);
    void signalStateCurrentCyclePaused(bool);
    void signalStateRunningAutoCalibration(bool);
    void signalStateRunningAutoBlank(bool);
    void signalStateInMaintenance(bool);
    void signalStateWaiting(bool);

protected slots:
    void slotVariableChanged();

private:

//    bool m_isInMaintenanceMode;

    CState m_stateInMaintenance;
    CState m_stateCycleIsRunning;
    CState m_stateCurrentCycleIsPaused;
    CState m_stateWillStopEndCycle;
    CState m_stateCycleAutoRunning;


    CVariableBool* m_localControlForced;

    //Gestion redémarage du cycle en cas d'arrêt du à une alarm
    void requestStopFromNewAlarm(CVariableAlarm * arg_alarm);
    void restartFromCanceledAlarm(CVariableAlarm* arg_alarm);
    void stopScheduler();

    QMap<QString, CVariableAlarm *> m_mapAlarmWhichStoppedScheduler;
    bool m_schedulerStoppedFromIHM;

    void removeVariableFromTree(IVariable* arg_var);
    static CAutomate* singleton;
    CAutomate();
    ~CAutomate();
    bool shouldQuit();

    QList<IVariable*> m_listLoggedVar;
    QList<IVariable*> m_listLoggedVarDebug;
    mutable QMutex m_mutex;

    //eStateScheduler m_stateScheduler;

    CScheduler* m_scheduler;
    CThreadDiag* m_threadDiag;
    CDisplayConf* m_displayConf;
    QMap<QString, ICycle*> m_listCycleMesures;
    QMap<QString, ICycle*> m_listCycleMaintenances;
    QMap<QString, ICycle*> m_listlCycleAutonomes;
    QList<CUnit*> m_listUnits;
    QMap<QString, ICom*> m_mapComs;
    QMap<QString, IVariable*> m_mappingCom;

    QMap<QString, IAction*> m_mapActions;
    QList<IAction*> m_listActions; //en redondance avec m_mapActions pour ne pas refaire niveau IHM

    ICommand* m_commandPlayStop;
    ICommand* m_commandStopEndCycle;
    ICommand* m_commandNextCycle;

    QMap<QString, IVariable*> m_mapVariables;
    QList<CVariableStream*> m_listStreams;
    QMap<QString, CModelExtensionCard*> m_mapExtCards;

    /*QList<CControlerCycle*> m_listCtrlCycleMesure;
    QList<CControlerCycle*> m_listCtrlCycleMaintenance;
    QList<CControlerCycle*> m_listCtrlCycleIO;*/

    int m_iClock;

    // The next function deliberatly not lock the mutex so internals can rely on them ensuring they have first locked the mutex.
    void addCyclePrivate(ICycle *cycle);
    void addVariablePrivate(const QString &name, IVariable *var);
    QList<ICycle*> getListCyclesPrivate(int cycleType = 0);
    QMap<QString, IVariable*> getMapVariablesPrivate();

    QString m_lang;
    bool m_debug;
    int m_countBeforeCheckLogFileToDelete;

};

Q_DECLARE_METATYPE(CAutomate::eStateStream)

#endif // CAUTOMATE_H
