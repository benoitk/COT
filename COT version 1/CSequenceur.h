#ifndef CSEQUENCEUR_H
#define CSEQUENCEUR_H

#include <QObject>

//GEstion de l'éxecution des cycles
class ICycle;
class CControlerCycle;
class CSequenceur : public QObject
{
	Q_OBJECT

public:
	
	//API
	QList<ICycle*> getListSequenceCyclesMesures();
	void setListSequenceCyclesMesures(QList<ICycle*>);

	//FIN API

	static CSequenceur* getInstance();

	void apendSequenceMesureRunCycle(ICycle*, int nbCycle);
	//void apendSequenceMesureRunCycle(CControlerCycle*, int nbCycle);
	void apendSequenceMesurePause(int minute);
	void initListSequenceCyclesMesures(QList<ICycle*>);

	void setSequenceMesure(QList<ICycle*>);

public slots:
	void slotRequestPlaySequenceMesure(); //démarre ou redémarre 
	void slotRequestPlayNextSequenceMesure();
	void slotRequestStopSequenceMesure();
	void slotRequestPauseSequenceMesure();
	void slotRequestUnPauseSequenceMesure();

	void slotPlaySequenceMesure();
	void slotPlayNextSequenceMesure();
	void slotPlayNextSequenceMaintenance();
	void slotPlayNextSequenceAutonome();

	void slotCycleMesureIsRunning();
	void slotCycleMesureIsStopped();
	void slotCycleMesureIsPaused();

signals:
	void signalRunCycleMesure();
	void signalPauseCycleMesure();
	void signalUnPauseCycleMesure();
	void signalStopCycleMesure();
	void signalRunCycleMaintenance();
	void signalPauseCycleMaintenance();
	void signalUnPauseCycleMaintenance();
	void signalStopCycleMaintenance();
	void signalRunCycleAutonome();
	void signalPauseCycleAutonome();
	void signalUnPauseCycleAutonome();
	void signalStopCycleAutonome();
	void signalGoToEndCycleMesure();
	void signalGetReadyForPlayNextCycleMesure();
	void signalGetReadyForPlayCycleMesure();


private:
	CSequenceur();
	~CSequenceur();

	void disconnectCycle(ICycle*);
	void setSequenceMesure();
	void playSequenceMaintenance(int id_cycle);
	void playSequenceAutonome();


	static CSequenceur* singleton;
	QList<ICycle*> m_listSequenceCyclesMesures;
	QList<ICycle*> m_listSequenceCyclesAutonomes;
	QList<ICycle*> m_listSequenceCyclesMaintenances;

	/*QList<CControlerCycle*> m_listSequenceCyclesMesure;
	QList<CControlerCycle*> m_listSequenceCyclesAutonome;
	QList<CControlerCycle*> m_listSequenceCyclesMaintenance;*/

	bool m_bPlaySequenceMesure;
	bool m_bPlaySequenceMaintenance;
	bool m_bPlaySequenceAutonome;

	bool m_bCycleMesurePaused;
	bool m_bCycleMesureRunning;

	QList<ICycle*>::iterator m_itListSequenceCyclesMesures; 

	ICycle* m_cycleMesureEnCours;
	ICycle* m_cycleMaintenanceEnCours;
	ICycle* m_cycleAutonomeEnCours;
};

#endif // CSEQUENCEUR_H
