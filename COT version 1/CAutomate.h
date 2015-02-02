#ifndef CAUTOMATE_H
#define CAUTOMATE_H

#include <QObject>

//Automade de gestion des cycles
class ICycle;
class CControlerCycle;
class CSequenceur;
class CAutomate : public QObject
{
	Q_OBJECT

public:
	CAutomate();
	~CAutomate();

	void setStateCycleMesure(int);
	void setStateCycleIO(int);
	void setStateMaintenance(int);

	void setStateStopCycleMesure();
	void setStateStopCycleIO();
	void setStateStopCycleMaintenance();
	void setStatePauseCycleMesure();
	void setStatePauseCycleIO();
	void setStatePauseCycleMaintenance();
	void setStateRunCycleMesure();
	void setStateRunCycleIO();
	void setStateRunCycleMaintenance();

	void addCycle(ICycle*);


public slots:
	void slotRunAutomate();

signals:
	void signalRunCycle(int);
	
private:
	int m_stateCycleMesure; //0 stoped, 1 run, 2 pause
	int m_stateCycleIO; //0 stoped, 1 run, 2 pause
	int m_stateCycleMaintenance; //0 stoped, 1 run, 2 pause

	CSequenceur* m_sequenceur;

	QList<ICycle*> m_listCycleMesure;
	QList<ICycle*> m_listCycleMaintenance;
	QList<ICycle*> m_listlCycleAutonome;

	/*QList<CControlerCycle*> m_listCtrlCycleMesure;
	QList<CControlerCycle*> m_listCtrlCycleMaintenance;
	QList<CControlerCycle*> m_listCtrlCycleIO;*/
	enum eStateCycle{CYCLE_RUN, CYLE_PAUSE, CYCLE_STOP};
	
};

#endif // CAUTOMATE_H
