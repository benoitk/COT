#ifndef CSCHEDULER_H
#define CSCHEDULER_H

#include <QObject>

//GEstion de l'éxecution des cycles
class ICycle;
class CControlerCycle;
class CScheduler : public QObject
{
    Q_OBJECT

public:

    //API
    QList<ICycle*> getListSequenceCyclesMesures();
    void setListSequenceCyclesMesures(QList<ICycle*>, bool = false );
    void addCycleMeasure(int index, ICycle*);
    void addCycleMeasure(ICycle*);
    void replaceCycleMeasureAt(int index, ICycle*);
    void removeCycleMeasureAt(int index);
    ICycle* getCycleMeasureAt(int index) const;

    QList<ICycle*> getListSequenceCyclesAutonomes();
    void setListSequenceCyclesAutonomes(QList<ICycle*> );
    void addCycleAutonome(int index, ICycle*);
    void addCycleAutonome(ICycle*);
    void replaceCycleAutonomeAt(int index, ICycle*);
    void removeCycleAutonomeAt(int index);
    ICycle* getCycleAutonomeAt(int index) const;

    QList<ICycle*> getListCyclesMaintenances();
    void setListCyclesMaintenances(QList<ICycle*> );
    void addCycleMaintenance(ICycle*);

    void removeCycleMeasure(ICycle *);
    void removeCycleMaintenance(ICycle *);
    void removeCycleAutonome(ICycle *);

    //FIN API

    static CScheduler* getInstance();

    void apendSequenceMeasureRunCycle(ICycle*, int nbCycle);
    //void apendSequenceMesureRunCycle(CControlerCycle*, int nbCycle);
    void apendSequenceMeasurePause(int minute);



public slots:
    void slotRequestPlaySequenceMesure(); //démarre ou redémarre
    void slotRequestPlayNextSequenceMesure();
    void slotRequestStopSequenceMesure();
    void slotRequestPauseSequenceMesure();
    void slotRequestUnPauseSequenceMesure();

    void slotPlaySequenceMeasure();
    void slotPlayNextSequenceMeasure();
    void slotPlayNextMaintenance();
    void slotPlayNextSequenceAutonome();

    void slotCycleMesureIsRunning();
    void slotCycleMesureIsStopped(bool withCriticalError);
    void slotCycleMesureIsPaused();

    void slotStartAllCyleAutonome();

signals:
    void signalUpdated();
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
    CScheduler();
    ~CScheduler();

    void disconnectCycle(ICycle*);
    void setSequenceMeasure();

    void playMaintenance(int id_cycle);
    void playSequenceAutonome();


    static CScheduler* singleton;

    QList<ICycle*> m_listSequenceCyclesMeasures;
    QList<ICycle*> m_listSequenceCyclesAutonomes;
    QList<ICycle*> m_listCyclesMaintenances;

    /*QList<CControlerCycle*> m_listSequenceCyclesMesure;
    QList<CControlerCycle*> m_listSequenceCyclesAutonome;
    QList<CControlerCycle*> m_listSequenceCyclesMaintenance;*/

    bool m_bPlaySequenceMesure;
    bool m_bPlayMaintenance;
    bool m_bPlaySequenceAutonome;

    bool m_bCycleMesurePaused;
    bool m_bCycleMesureRunning;

    QList<ICycle*>::iterator m_itListSequenceCyclesMesures;

    ICycle* m_cycleMeasureEnCours;
    ICycle* m_cycleMaintenanceEnCours;
    ICycle* m_cycleAutonomeEnCours;
};

#endif // CSCHEDULER_H
