#ifndef ICYCLE_H
#define ICYCLE_H

#include <QObject>
#include "qmutex.h"
#include <QTimer>
#include "qmap.h"

enum enumTypeCycle{
    e_cycle_invalid = -1,
    e_cycle_all = 0,
    e_cycle_measure,
    e_cycle_autonome,
    e_cycle_maintenance,
    e_cycle_pause};

class IAction;
class CStep;
class CVariableStream;
class CScheduler;
class ICycle : public QObject
{
    Q_OBJECT

public:
    explicit ICycle(CScheduler *parent);
    ICycle(const QVariantMap &mapCycle, CScheduler *parent);
//    ICycle();

    virtual enumTypeCycle getType()const=0;
    virtual void addAction(float arg_step, IAction* action);
    void removeAction(IAction* arg_action);
    virtual QString getName()const ;
    virtual void setName(const QString&);
    virtual QString getLabel()const;
    virtual void setLbl(const QString&);
    virtual QString getRelatedStreamName()const;
    virtual void setRelatedStreamName(const QString &name);
    virtual CVariableStream* getRelatedStream()const;
    virtual QList<CStep*> getListSteps()const;
    virtual void setListSteps(const QList<CStep *> &steps, CStep *stopStep = Q_NULLPTR);
    virtual CStep* getStepStop()const;
    virtual bool isRunning() const;
    virtual bool isPaused()const;
    virtual int getCurrentStepIndex() const;
    virtual QVariantMap serialize();

    bool isStreamRelated()const;
    CStep *getStep(int index) const;

    static QString typeToString(enumTypeCycle type);

    bool swapStep(float from, float to);
    bool copySteps(float from, float length, float to);
    bool copyStep(float from, float to);
    bool moveSteps(float from, float length, float to);
    bool moveStep(float from, float to);
    bool deleteSteps(float from, float length);
    bool deleteStep(float at);
    virtual CStep* addStep(float pos, const QString& lbl);

    virtual void updateCycleInfosStep(float arg_numStep, QString arg_info);

    virtual void updateCycleInfosAction(QString arg_info);
    virtual void updateCycleInfosCountStep();

    virtual CScheduler* getScheduler();

public slots:
    virtual void slotUpdateCycleInfosNumStep();
    virtual void slotRunCycle()=0;
    virtual void slotPauseCycle()=0;
    virtual void slotUnPauseCycle()=0;
    virtual void slotStopCycle()=0;
    virtual void slotStopEndCycle()=0;
    virtual void slotGoToEndCycle()=0;
    virtual void slotGoToStepCycle(int)=0;
    virtual void slotGetReadyForPlayNextCycle()=0;
    virtual void slotGetReadyForPlayCycle()=0;

    virtual void slotExecNextStep()=0;

    void slotValidateEditing();
    void slotCancelEditing();

signals:
    void signalStopped(ICycle*);
    void signalPaused();
    void signalRunning();
    void signalReadyForPlayNextCycle(ICycle*);
    void signalReadyForPlayCycle();
protected:

    void startEditing();
    void clearSavedListSteps();
    void shiftAllSteps(float arg_from, float arg_shifting, int arg_index=0);
    void abortCycle();

    bool m_isRunning;
    bool m_isPaused;
    float m_numStepInfo;
    CStep* m_stepStop;
    QList<CStep*> m_listSteps;
    QList<CStep*> m_savedListSteps;
    QList<CStep*>::iterator m_itListStepsPasEnCours;


    //QString m_streamName;
    QString m_label;
    int m_idCycle;
    QString m_name;
    QMap<QThread* ,QTimer*> m_mapTimerSchedulerStep;
    QMap<QThread* ,QTimer*> m_mapTimerInfoNumStep;

    bool m_editInProgress;
    QMutex m_mutex;
    CScheduler*  m_scheduler;

};

#endif // ICYCLE_H
