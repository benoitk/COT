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
    CCyclePause(const QVariantMap&, QObject* parent);
    CCyclePause(int temps, QObject* parent = Q_NULLPTR);
    CCyclePause(int temps);
    ~CCyclePause();


    enumTypeCycle getType()const Q_DECL_OVERRIDE;


    QVariantMap serialize() Q_DECL_OVERRIDE;
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


    QThread m_thread;

};

#endif // CCYCLEPAUSE_H
