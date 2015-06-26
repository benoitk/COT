#ifndef CACTIONTEST_H
#define CACTIONTEST_H

#include "IAction.h"

#include "qrunnable.h"

class IVariable;
class CActionTest : public IAction, QRunnable
{
    Q_OBJECT

public:
    CActionTest(const QVariantMap&, QObject *parent);
    ~CActionTest();


    void run() Q_DECL_OVERRIDE; //fom QRunnable

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    bool waitUntilFinished() Q_DECL_OVERRIDE;
    bool finishedWithCriticalError() Q_DECL_OVERRIDE;

    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;


private:
    enum eContidion{m_eEqualToSetpoint=0, m_eSuperiorToSetpoint, m_eInferiorToSetPoint};
    IVariable* m_setpoint;
    IVariable* m_target;
    IVariable* m_result;
    IVariable* m_waiting;
    eContidion m_condition;
    IVariable* m_errorMargin;
    IVariable* m_timeout;
    bool m_criticalError;
};

#endif // CACTIONTEST_H
