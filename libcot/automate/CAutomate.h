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
class CSequenceur;
class IVariable;
class CModelExtensionCard;
class INetwork;
class IAction;
class CUnit;
class CDisplayConf;
class CAutomate : public QObject, IComObserver
{
	Q_OBJECT

public:
	
	//use for API 
	QList<CModelExtensionCard*> getListExtensions();
    QList<ICycle*> getListCycles(int cycleType = 0);
	QList<IAction*> getListActions();
	QList<CUnit*> getListUnits();
	QMap<QString, IVariable*> getMapVariables();
	QMap<QString, IVariable*> getMapStreams();
	void setMapVariables(QMap<QString, IVariable*>);
    QMap<QString, QStringList> getMapStreamsMeasures() const;
    void setMapStreamsMeasures(QMap<QString, QStringList>);
    QMap<QString, QStringList> getMapStreamsCycles() const;
    void setMapStreamsCycles(QMap<QString, QStringList>);
    CDisplayConf* getDisplayConf()const;

    static QString formatHistoryEntry(const QString &name, const QDateTime &dateTime);

    // KDAB: Needed api
    template <typename T, typename Val>
    void createVariable(const QString &name, const Val &val) {
        T * t = new T;
        t->setName(name);
        t->setLabel(name);
        t->setValue(val);
        addVariable(name, t);
    }

    QStringList getStreams() {
        return QStringList() << "stream_1" << "stream_2";
    }

    //use CVariableVoie::getVariables()
    QStringList getStreamVariables(const QString &stream) {
        static QMap<QString, QStringList> variables;

        if (variables.isEmpty()) {
            variables["stream_1"] = QStringList() << "active_state" << "status" << "defaut_eau";
            variables["stream_2"] = QStringList() << "active_state_2" << "var_stream" << "measure";

            createVariable<CVariableBool, bool>("active_state", true);
            createVariable<CVariableInputBool, bool>("status", true);
            createVariable<CVariableInputBool, bool>("defaut_eau", true);

            createVariable<CVariableBool, bool>("active_state_2", true);
            createVariable<CVariableString, QString>("var_stream", "stream 42");
            createVariable<CVariableInputFloat, double>("measure", 2.00);
        }

        return variables.value(stream);
    }

    //use getMapStream
    QMap<QString, QStringList> getStreamMeasures(const QString &stream) {
        QMap<QString, QMap<QString, QStringList>> measures;

        if (measures.isEmpty()) {
            QMap<QString, QStringList> &stream1 = measures["stream_1"];
            stream1["measure_1"] = QStringList() << "coeff" << "measure_silice";
            stream1["measure_2"] = QStringList() << "coeff_2" << "measure_silice_2";

            createVariable<CVariableFloat, double>("coeff", 6.00);
            createVariable<CVariableFloat, double>("measure_silice", 6.00);
            createVariable<CVariableFloat, double>("coeff_2", 2.00);
            createVariable<CVariableFloat, double>("measure_silice_2", 2.00);

            QMap<QString, QStringList> &stream2 = measures["stream_2"];
            stream2["measure_3"] = QStringList() << "coeff_3" << "measure_silice_3";
            stream2["measure_4"] = QStringList() << "coeff_4" << "measure_silice_4";

            createVariable<CVariableFloat, double>("coeff_3", 6.00);
            createVariable<CVariableFloat, double>("measure_silice_3", 6.00);
            createVariable<CVariableFloat, double>("coeff_4", 6.00);
            createVariable<CVariableFloat, double>("measure_silice_4", 2.00);
        }

        return measures.value(stream);;
    }
	//FIN API

    enum eStateCycle{CYCLE_STATE_RUN = 1, CYCLE_STATE_PAUSE = 2, CYCLE_STATE_STOP = 0};
	enum eStateAutomate{GENERAL_DEFAULT, RUNNING};
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

	IVariable* getVariable(const QString&);
    QList<IVariable *> getVariables(const QStringList&);
	void addVariable(const QString&, IVariable*);
	void addStream(const QString&, IVariable*);
    void addUnit(CUnit*);


	CModelExtensionCard* getExtensionCard(QString);
	void addExtensionCard(QString, CModelExtensionCard*); 


	//IComObserver
    IVariable* getVariable(const QString &addr_var)const Q_DECL_OVERRIDE;
	void setCom(ICom*);

	void initConfig();
    void quit();

public slots:
	void slotRunAutomate();
    // DO NOT add any other slots here. They will never run, since the automat thread
    // doesn't go back to the event loop.

signals:
	void signalRunCycle(int);
    // KDAB: Needed api
    // When the streams section changed
    void signalStreamsChanged();
    // When the display section is changed
    void signalDisplayChanged();
    // When the cycles section is changed
    void signalCyclesChanged();
    // When the value of a variable changed
    void signalVariableChanged(const QString &name, const QDateTime &dateTime = QDateTime());
    // When internal state of a general cycle changed
    void signalCycleChanged(const QString &name);
    // When internal state of the current running maintenance cycle changed
    void signalCurrentMaintenanceCycleChanged(const QString &name);

   
    //desc : nouvelle ligne d'alarme 
	//entrées : identifiant(pour acquitement), date, heure et descriptif  
    void signalUpdateAlarms(int, const QDateTime &, const QString &);
	//desc : Nouvelle ligne d'historique de mesure
	//entrées : date, heure, descriptif
    void signalUpdateHistory(const QDateTime&, const QString&);
	//desc : Etat changé : En court, en pause, en arrêt
	//entrées : enum de l'état du cycle en cours
	void signalUpdateStateCycle(CAutomate::eStateCycle); 
	//desc : Etat changé : En défaut, en cycle, en maintenance
	//entrées : enum de l'état de l'automate
	void signalUpdateStateAutomoate(CAutomate::eStateAutomate); 
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
	void signalUpdateStateStream(CAutomate::eStateStream); 
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
    void signalDisplayUpdated();
    void signalBindsUpdated();
    void signalActionsUpdated();
    void signalCyclesUpdated();
    void signalShcedulerUpdated();
    void signalStreamsUpdated();


private:
	static CAutomate* singleton;
	CAutomate();
	~CAutomate();
    bool shouldQuit();

    mutable QMutex m_mutex;
    bool m_quit;

	QList<INetwork*> m_listNetworks;
	QList<CModelExtensionCard*> m_listExtCards;
    eStateCycle m_stateCycleMesure; //0 stoped, 1 run, 2 pause
    eStateCycle m_stateCycleIO; //0 stoped, 1 run, 2 pause
    eStateCycle m_stateCycleMaintenance; //0 stoped, 1 run, 2 pause

	CSequenceur* m_sequenceur;
    CDisplayConf* m_displayConf;
    QMap<QString, ICycle*> m_listCycleMesures;
    QMap<QString, ICycle*> m_listCycleMaintenances;
    QMap<QString, ICycle*> m_listlCycleAutonomes;
	QList<IAction*> m_listActions;
    QList<CUnit*> m_listUnits;

	QMap<QString, IVariable*> m_mapVariables;
	QMap<QString, IVariable*> m_mapStreams;
    QMap<QString, QStringList> m_mapStreamsMeasures;
    QMap<QString, QStringList> m_mapStreamsCycles;


	/*QList<CControlerCycle*> m_listCtrlCycleMesure;
	QList<CControlerCycle*> m_listCtrlCycleMaintenance;
	QList<CControlerCycle*> m_listCtrlCycleIO;*/
	
};

#endif // CAUTOMATE_H
