#ifndef CACTIONTEST_H
#define CACTIONTEST_H

#include "IAction.h"

#include "qrunnable.h"

class IVariable;
class CActionTest : public IAction, QRunnable
{
public:


    CActionTest(const QVariantMap&, QObject *parent);
    ~CActionTest();


    void run() Q_DECL_OVERRIDE; //fom QRunnable

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    bool waitUnitlFinished() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

private:
    enum eContidion{m_eEqual=0, m_eDiffUp, m_eDiffDown};
    IVariable* m_setpoint;
    IVariable* m_target;
    IVariable* m_result;
    IVariable* m_waiting;
    eContidion m_condition;
    IVariable* m_errorMargin;
    IVariable* m_timeout;

};

#endif // CACTIONTEST_H
