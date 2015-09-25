#ifndef CCYCLEMESURE_H
#define CCYCLEMESURE_H

#include "ICycle.h"
#include <qlinkedlist.h>

#include "qmutex.h"
#include "qthread.h"

class CLinkAction;
class QTimer;
class CCycleMesure : public ICycle
{
    Q_OBJECT

public:
    CCycleMesure(QObject *parent = Q_NULLPTR);
    CCycleMesure(const QVariantMap&, QObject *parent);
    ~CCycleMesure();


    enumTypeCycle getType()const Q_DECL_OVERRIDE;

    QVariantMap serialize() Q_DECL_OVERRIDE;
public slots:
    void slotRunCycle() Q_DECL_OVERRIDE;
    void slotPauseCycle() Q_DECL_OVERRIDE;
    void slotStopCycle() Q_DECL_OVERRIDE;
    void slotUnPauseCycle() Q_DECL_OVERRIDE;
    void slotStopEndCycle() Q_DECL_OVERRIDE;
    void slotGoToEndCycle() Q_DECL_OVERRIDE;
    void slotGoToStepCycle(int) Q_DECL_OVERRIDE;
    void slotGetReadyForPlayNextCycle() Q_DECL_OVERRIDE;
    void slotGetReadyForPlayCycle() Q_DECL_OVERRIDE;

    void slotExecNextStep() Q_DECL_OVERRIDE;


    void slotStepFinished(CStep*);

private:

    int m_timeout;
    QThread m_thread;



};
#endif // CCYCLEMESURE_H
