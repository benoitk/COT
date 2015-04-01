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
class CAutomate : public QObject, IComObserver
{
	Q_OBJECT

public:
	
    enum eStateCycle{CYCLE_RUN, CYCLE_PAUSE, CYCLE_STOP};
	enum eStateAutomate{GENERAL_DEFAULT, RUNNING};
	enum eStateStream{STREAM_DEFAULT, WATER_DEFAULT, ACTIVE, INACTIVE};
	static CAutomate* getInstance();

	void setStateCycleMesure(eStateCycle);
	eStateCycle getStateCycleMesure();
	void setStateCycleIO(eStateCycle);
	eStateCycle getStateCycleIO();
	void setStateCycleMaintenance(eStateCycle);
	eStateCycle getStateCycleMaintenance();

	

	void addCycle(ICycle*);

	IVariable* getVariable(QString);
	void addVariable(QString, IVariable*);

	CModelExtensionCard* getExtensionCard(QString);
	QList<CModelExtensionCard*> getListExtension(QString);
	void addExtensionCard(QString, CModelExtensionCard*); 


	//IComObserver
	IVariable* getVariable(QString addr_var)const;
	void setCom(ICom*);

	void initConfig();
public slots:
	void slotRunAutomate();

signals:
	void signalRunCycle(int);
	
private:
	static CAutomate* singleton;
	CAutomate();
	~CAutomate();

	QList<INetwork*> m_listNetwork;
	QList<CModelExtensionCard*> m_listExtCard;
	int m_stateCycleMesure; //0 stoped, 1 run, 2 pause
	int m_stateCycleIO; //0 stoped, 1 run, 2 pause
	int m_stateCycleMaintenance; //0 stoped, 1 run, 2 pause

	CSequenceur* m_sequenceur;

	QList<ICycle*> m_listCycleMesure;
	QList<ICycle*> m_listCycleMaintenance;
	QList<ICycle*> m_listlCycleAutonome;

	QMap<QString, IVariable*> m_mapVariables;
	QMutex m_mutexVariablesAccess;



	/*QList<CControlerCycle*> m_listCtrlCycleMesure;
	QList<CControlerCycle*> m_listCtrlCycleMaintenance;
	QList<CControlerCycle*> m_listCtrlCycleIO;*/
	
};

#endif // CAUTOMATE_H
