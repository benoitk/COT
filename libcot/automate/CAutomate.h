#ifndef CAUTOMATE_H
#define CAUTOMATE_H

#include "IComObserver.h"

// KDAB: Remove me
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

#include <QObject>
#include <QStringList>
#include <QDateTime>
#include "qmap.h"
#include "qmutex.h"

//Automade de gestion des cycles
class ICycle;
class CControlerCycle;
class CScheduler;
class IVariable;
class CModelExtensionCard;
class IAction;
class CUnit;
class CDisplayConf;
class IOrgan;
class CVariableStream;
class CVariableMeasure;

class CAutomate : public QObject, IComObserver
{
    Q_OBJECT

public:

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

    void playScheduler();
    void stopScheduler();
    void pauseScheduler();
    //FIN API

    static QString formatHistoryEntry(const QString &name, const QDateTime &dateTime);

    enum eStateCycle{CYCLE_STATE_RUN = 1, CYCLE_STATE_PAUSE = 2, CYCLE_STATE_STOP = 0};
    enum eStateAutomate{GENERAL_DEFAULT, RUNNING,PAUSED, CALIBRATION, WAITING,STOPPED};
    enum eStateStream{STREAM_DEFAULT, WATER_DEFAULT, ACTIVE, INACTIVE};
    static CAutomate* getInstance();

    void setStateCycleMesure(eStateCycle);
    eStateCycle getStateCycleMesure();
    void setStateCycleIO(eStateCycle);
    eStateCycle getStateCycleIO();
    void setStateCycleMaintenance(eStateCycle);
    eStateCycle getStateCycleMaintenance();
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
    void addAction(IAction*);
    void delAction(IAction*);
    void delAction(const QString&);
    void delVariable(IVariable *ivar);

    CModelExtensionCard* getExtensionCard(const QString&);
    void addExtensionCard(const QString&, CModelExtensionCard*);

    void delCycle(ICycle *cycle);
    void delStream(CVariableStream *ivar);

    CScheduler* getSequencer()const;

    //IComObserver
    IVariable* getVariableByAddr(const QString &addr_var)const Q_DECL_OVERRIDE;
    void setCom(ICom*) Q_DECL_OVERRIDE;

    void addVariableToMappingCom(IVariable*);

    void initConfig();
    void quit();


public slots:
    void slotClock();
    void slotStartAutomate();
signals:
    void signalRunCycle(int);
    // KDAB: Needed api
    // When the value of a variable changed
    void signalVariableChanged(const QString &name, const QDateTime &dateTime);
    // When internal state of a general cycle changed
    void signalCycleChanged(const QString &name);
    // When internal state of the current running maintenance cycle changed
    void signalCurrentMaintenanceCycleChanged(const QString &name);
    //Signal to update all data on the graphic
    void signalUpdatePlotting();


    //desc : Etat changé : En court, en pause, en arrêt
    //entrées : enum de l'état du cycle en cours
    void signalUpdateStateCycle(CAutomate::eStateCycle);
    //desc : Etat changé : En défaut, en cycle, en maintenance
    //entrées : enum de l'état de l'automate
    void signalUpdateStateAutomate(CAutomate::eStateAutomate);
    //desc : Pas en cours changé
    //entrées : pas en cours; label du pas
    void signalUpdateCurrentStep(float, const QString &);
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

protected slots:
    void slotVariableChanged();

private:
    static CAutomate* singleton;
    CAutomate();
    ~CAutomate();
    bool shouldQuit();

    mutable QMutex m_mutex;

    eStateCycle m_stateCycleMesure; //0 stoped, 1 run, 2 pause
    eStateCycle m_stateCycleIO; //0 stoped, 1 run, 2 pause
    eStateCycle m_stateCycleMaintenance; //0 stoped, 1 run, 2 pause

    CScheduler* m_scheduler;
    CDisplayConf* m_displayConf;
    QMap<QString, ICycle*> m_listCycleMesures;
    QMap<QString, ICycle*> m_listCycleMaintenances;
    QMap<QString, ICycle*> m_listlCycleAutonomes;
    QList<CUnit*> m_listUnits;
    QMap<QString, ICom*> m_mapComs;
    QMap<QString, IVariable*> m_mappingCom;

    QMap<QString, IAction*> m_mapActions;
    QList<IAction*> m_listActions; //en redondance avec m_mapActions pour ne pas refaire niveau IHM
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
};

Q_DECLARE_METATYPE(CAutomate::eStateAutomate)
Q_DECLARE_METATYPE(CAutomate::eStateStream)

#endif // CAUTOMATE_H
