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
	QList<ICycle*> getListCycles();
	QList<IAction*> getListActions();
	QList<CUnit*> getListUnits();
	QMap<QString, IVariable*> getMapVariables();
	void setMapVariables(QMap<QString, IVariable*>);
    QMap<QString, QList<QString>> getMapStreamsMeasures() const;
    void setMapStreamsMeasures(QMap<QString, QList<QString>>);
    CDisplayConf* getDisplayConf()const;

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

    QMap<QString, QStringList> getStreamMeasures(const QString &stream) {
        QMap<QString, QMap<QString, QStringList>> measures;

        if (measures.isEmpty()) {
            QMap<QString, QStringList> &stream1 = measures["stream_1"];
            stream1["measure_1"] = QList<QString>() << "coeff" << "measure_silice";
            stream1["measure_2"] = QList<QString>() << "coeff_2" << "measure_silice_2";

            createVariable<CVariableFloat, double>("coeff", 6.00);
            createVariable<CVariableFloat, double>("measure_silice", 6.00);
            createVariable<CVariableFloat, double>("coeff_2", 2.00);
            createVariable<CVariableFloat, double>("measure_silice_2", 2.00);

            QMap<QString, QStringList> &stream2 = measures["stream_2"];
            stream2["measure_3"] = QList<QString>() << "coeff_3" << "measure_silice_3";
            stream2["measure_4"] = QList<QString>() << "coeff_4" << "measure_silice_4";

            createVariable<CVariableFloat, double>("coeff_3", 6.00);
            createVariable<CVariableFloat, double>("measure_silice_3", 6.00);
            createVariable<CVariableFloat, double>("coeff_4", 6.00);
            createVariable<CVariableFloat, double>("measure_silice_4", 2.00);
        }

        return measures.value(stream);;
    }
	//FIN API


	enum eStateCycle{CYCLE_RUN, CYLE_PAUSE, CYCLE_STOP};
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

	IVariable* getVariable(const QString&);
	void addVariable(const QString&, IVariable*);
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
    void signalStreamsChanged(); // When the streams section changed
    void signalDisplayChanged(); // When the display section is changed
    void signalVariableChanged(const QString &name); // when the value of a variable changed

private:
	static CAutomate* singleton;
	CAutomate();
	~CAutomate();
    bool shouldQuit();

	QList<INetwork*> m_listNetworks;
	QList<CModelExtensionCard*> m_listExtCards;
	int m_stateCycleMesure; //0 stoped, 1 run, 2 pause
	int m_stateCycleIO; //0 stoped, 1 run, 2 pause
	int m_stateCycleMaintenance; //0 stoped, 1 run, 2 pause

	CSequenceur* m_sequenceur;
    CDisplayConf* m_displayConf;
	QList<ICycle*> m_listCycleMesures;
	QList<ICycle*> m_listCycleMaintenances;
	QList<ICycle*> m_listlCycleAutonomes;
	QList<IAction*> m_listActions;
    QList<CUnit*> m_listUnits;

	QMap<QString, IVariable*> m_mapVariables;
    mutable QMutex m_mutex;
	QMap<QString, QList<QString>> m_mapStreamsMeasures;

    bool m_quit;

	/*QList<CControlerCycle*> m_listCtrlCycleMesure;
	QList<CControlerCycle*> m_listCtrlCycleMaintenance;
	QList<CControlerCycle*> m_listCtrlCycleIO;*/
	
};

#endif // CAUTOMATE_H
