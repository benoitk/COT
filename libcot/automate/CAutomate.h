#ifndef CAUTOMATE_H
#define CAUTOMATE_H

#include "IComObserver.h"

#include <QObject>
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
    void signalStreamsMeasuresChanged(); // When the json streams section changed
    void signalStreamMeasureChanged(const QString &measure); // when the value of a measure changed
	
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
