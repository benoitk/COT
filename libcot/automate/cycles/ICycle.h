#ifndef ICYCLE_H
#define ICYCLE_H

#include <QObject>


enum eTypeCycle{CYCLE_INVALID = -1, CYCLE_ALL = 0, CYCLE_MESURE, CYCLE_AUTONOME, CYCLE_MAINTENANCE, CYCLE_PAUSE};

class IAction;
class CStep;
class ICycle : public QObject
{
    Q_OBJECT

public:
    explicit ICycle(QObject *parent);
    ICycle();
    ~ICycle();

    virtual void addAction(int, IAction*)=0;
    virtual eTypeCycle getType()const=0;
    virtual void setType(eTypeCycle)=0;
    virtual QString getName()const =0;
    virtual void setName(const QString&)=0;
    virtual QString getLbl()const=0;
    virtual void setLbl(const QString&)=0;
    virtual QString getRelatedStreamName()const=0;
    virtual void setRelatedStreamName(const QString &name)=0;
    virtual QList<CStep*> getListSteps()const=0;
    virtual CStep* getStepStop()const=0;
    virtual bool isRunning()=0;
    virtual bool isPaused()=0;
    virtual int getCurrentStepIndex() const = 0;

    bool isStreamRelated()const;
    CStep *getStep(int index) const;

    static QString typeToString(eTypeCycle type);


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

signals:
    void signalStopped();
    void signalPaused();
    void signalRunning();
    void signalReadyForPlayNextCycle();
    void signalReadyForPlayCycle();


};

#endif // ICYCLE_H
