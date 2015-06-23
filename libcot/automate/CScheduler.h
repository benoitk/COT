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
    typedef QPair<ICycle *, int> CyclePair;

    QList<ICycle*> getListSequenceCyclesMesures();
    void setListSequenceCyclesMesures(QList<ICycle*> );
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


    // SERES_TODO: Proposed api by KDAB, used by the configurator. (COT-61)
    // To be entirely implemented / used by the sequencer.
    void addCycle(const CyclePair &pair);
    void replaceCycleAt(int index, const CyclePair &pair);
    void removeAt(int index);
    void removeCycleMeasure(ICycle *);
    void removeCycleMaintenance(ICycle *);
    void removeCycleAutonome(ICycle *);
    CyclePair getCycleAt(int index) const;
    QList<CyclePair> getCycles() const;

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

    void slotPlaySequenceMesure();
    void slotPlayNextSequenceMesure();
    void slotPlayNextMaintenance();
    void slotPlayNextSequenceAutonome();

    void slotCycleMesureIsRunning();
    void slotCycleMesureIsStopped();
    void slotCycleMesureIsPaused();

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
    void setSequenceMesure();
    void playMaintenance(int id_cycle);
    void playSequenceAutonome();


    static CScheduler* singleton;

    //QList<CyclePair> m_listSequenceCycles;

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

    ICycle* m_cycleMesureEnCours;
    ICycle* m_cycleMaintenanceEnCours;
    ICycle* m_cycleAutonomeEnCours;
};

#endif // CSCHEDULER_H
