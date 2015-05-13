#ifndef CCYCLEPAUSE_H
#define CCYCLEPAUSE_H

#include "ICycle.h"
#include "qthread.h"
class QTimer;
class CCyclePause : public ICycle
{
    Q_OBJECT

public: //acces multithread possible sur tout les get, penser au mutex sur tous les accès aux variables.
    CCyclePause(QObject *parent = Q_NULLPTR);
    CCyclePause(const QVariantMap&);
    CCyclePause(int temps, QObject* parent = Q_NULLPTR);
    CCyclePause(int temps);
    ~CCyclePause();

    void addAction(int, IAction*) Q_DECL_OVERRIDE;
    eTypeCycle getType()const Q_DECL_OVERRIDE;
    void setType(eTypeCycle) Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLbl(const QString&) Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString&) Q_DECL_OVERRIDE;

    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    void setRelatedStreamName(const QString &name) Q_DECL_OVERRIDE;
    QList<CStep*> getListSteps()const Q_DECL_OVERRIDE;
    CStep* getStepStop()const Q_DECL_OVERRIDE;
    int getCurrentStepIndex() const Q_DECL_OVERRIDE;

    bool isRunning() Q_DECL_OVERRIDE;
    bool isPaused() Q_DECL_OVERRIDE;

public slots:
    void slotRunCycle() Q_DECL_OVERRIDE;
    void slotPauseCycle() Q_DECL_OVERRIDE;
    void slotUnPauseCycle() Q_DECL_OVERRIDE;
    void slotStopCycle() Q_DECL_OVERRIDE;
    void slotStopEndCycle() Q_DECL_OVERRIDE;
    void slotGoToEndCycle() Q_DECL_OVERRIDE;
    void slotGoToStepCycle(int) Q_DECL_OVERRIDE;
    void slotGetReadyForPlayNextCycle() Q_DECL_OVERRIDE;
    void slotGetReadyForPlayCycle() Q_DECL_OVERRIDE;

    void slotExecNextStep() Q_DECL_OVERRIDE;


private :

    void initTimer();

    QTimer* m_timer;
    int m_iTimer;
    int m_iTempsCycle;
    QString m_name;
    QString m_label;
    QString m_streamName;

    QThread m_thread;

    CStep* m_stepStop;
    QList<CStep*> m_listSteps;

};

#endif // CCYCLEPAUSE_H
