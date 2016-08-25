#ifndef CSCHEDULER_H
#define CSCHEDULER_H

#include <QObject>

//GEstion de l'éxecution des cycles
class ICycle;
class CControlerCycle;
class ISequenceMaintenanceAuto;
class CScheduler : public QObject
{
    Q_OBJECT

public:

    bool isCyclesRunning();

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

    QList<ISequenceMaintenanceAuto*> getListCycleMaintenanceAuto();
    void addCycleMaintenanceAuto(ISequenceMaintenanceAuto*);

    void removeCycleMeasure(ICycle *);
    void removeCycleMaintenance(ICycle *);
    void removeCycleAutonome(ICycle *);

    //FIN API

    static CScheduler* getInstance();

    void apendSequenceMeasureRunCycle(ICycle*, int nbCycle);
    //void apendSequenceMesureRunCycle(CControlerCycle*, int nbCycle);
    void apendSequenceMeasurePause(int minute);

    QString getCycleInProgressName();


public slots:
    void slotRequestPlaySequenceMesure(); //démarre ou redémarre
    void slotRequestPlayNextSequenceMesure();
    void slotRequestStopSequence();
    void slotRequestStopEndCycleSequence();
    void slotRequestCancelStopSequenceEndCycle();
    void slotRequestPauseSequenceMesure();
    void slotRequestUnPauseSequenceMesure();

    void slotPlaySequenceMeasure();
    void slotPlayNextSequenceMeasure();
    void slotPlayNextMaintenance();
    void slotPlayNextSequenceAutonome();

    void slotCycleMesureIsRunning();
    void slotCycleIsStopped();
    void slotCycleMesureIsPaused();

    void slotPlayMaintenance(const QString& arg_cycleName);

    void slotStartAllCyleAutonome();

signals:
    void signalUpdated();
    void signalRunCycle();
    void signalPauseCycle();
    void signalUnPauseCycle();
    void signalStopCycle();
    void signalRunCycleAutonome();
    void signalPauseCycleAutonome();
    void signalUnPauseCycleAutonome();
    void signalStopCycleAutonome();
    void signalGoToEndCycleMesure();
    void signalGetReadyForPlayNextCycleMesure();
    void signalGetReadyForPlayCycleMesure();
    void signalCycleIsStopped(const QString&);


private:
    CScheduler();
    ~CScheduler();

    void disconnectCycle(ICycle*);

    void setSequence(bool isMaintenance=false);

    ISequenceMaintenanceAuto* haveToPlaySequenceMaintenanceAuto();
    void playMaintenance(int id_cycle);
    void playSequenceAutonome();


    static CScheduler* singleton;

    QList<ICycle*> m_listSequenceCyclesMeasures;
    QList<ICycle*> m_listSequenceCyclesAutonomes;
    QList<ICycle*> m_listCyclesMaintenances;
    QList<ISequenceMaintenanceAuto*> m_listSequenceCyclesMaintenancesAuto;

    QList<ICycle*>::iterator m_itListSequenceCyclesMesures;

    bool m_haveToStopEndCycle;
    ICycle* m_cycleEnCours;
};


class ISequenceMaintenanceAuto: public QObject
{
    Q_OBJECT
public :
    virtual bool haveToBeRun()=0;
    virtual void reset()=0;
    virtual QVariantMap serialize()=0;
    virtual ICycle* getCycle();
public:
    ISequenceMaintenanceAuto(const QVariantMap&,  QObject *parent);
protected:
    ICycle* m_cycle;
};
class IVariable;
class CSequenceMaintenanceAutoEveryNCycles : public ISequenceMaintenanceAuto
{
public:
    CSequenceMaintenanceAutoEveryNCycles(const QVariantMap&,  QObject *parent);
    bool haveToBeRun() Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
 private:
    IVariable* m_nbCycle;
    int m_cpt;
};
class CSequenceMaintenanceAutoUnknow : public ISequenceMaintenanceAuto
{
public:
    CSequenceMaintenanceAutoUnknow(const QVariantMap&,  QObject *parent);
    bool haveToBeRun() Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
};
class CSequenceMaintenanceFactory : public QObject
{
    Q_OBJECT
public:
    static ISequenceMaintenanceAuto* build(const QVariantMap&,  QObject *parent);
};

#endif // CSCHEDULER_H
