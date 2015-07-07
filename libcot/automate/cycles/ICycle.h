#ifndef ICYCLE_H
#define ICYCLE_H

#include <QObject>
#include "qmutex.h"

enum eTypeCycle{CYCLE_INVALID = -1, CYCLE_ALL = 0, CYCLE_MESURE, CYCLE_AUTONOME, CYCLE_MAINTENANCE, CYCLE_PAUSE};

class IAction;
class CStep;
class CVariableStream;
class ICycle : public QObject
{
    Q_OBJECT

public:
    explicit ICycle(QObject *parent);
    ICycle(const QVariantMap &mapCycle, QObject *parent);
    ICycle();

    virtual eTypeCycle getType()const=0;
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
    virtual QVariantMap serialise();

    bool isStreamRelated()const;
    CStep *getStep(int index) const;

    static QString typeToString(eTypeCycle type);

     bool swapStep(float from, float to);
     bool copySteps(float from, float length, float to);
     bool copyStep(float from, float to);
     bool moveSteps(float from, float length, float to);
     bool moveStep(float from, float to);
     bool deleteSteps(float from, float length);
     bool deleteStep(float at);
     virtual CStep* addStep(float pos, const QString& lbl);

public slots:
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
    void signalStopped(bool withCriticalError);
    void signalPaused();
    void signalRunning();
    void signalReadyForPlayNextCycle();
    void signalReadyForPlayCycle();
protected:
    void startEditing();
    void clearSavedListSteps();
    bool m_isRunning;
    bool m_isPaused;

    CStep* m_stepStop;
    QList<CStep*> m_listSteps;
    QList<CStep*> m_savedListSteps;
    QList<CStep*>::iterator m_itListStepsPasEnCours;

    //QString m_streamName;
    QString m_label;
    int m_idCycle;
    QString m_name;

    bool m_editInProgress;
    QMutex m_mutex;
};

#endif // ICYCLE_H
