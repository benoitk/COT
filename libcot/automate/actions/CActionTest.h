#ifndef CACTIONTEST_H
#define CACTIONTEST_H

#include "IAction.h"

#include "qrunnable.h"

class IVariable;
class CVariableBool;
class IVariableInput;
class CActionTest : public IAction, QRunnable
{
    Q_OBJECT

public:
    CActionTest(const QVariantMap&, QObject *parent);
    ~CActionTest();


    void run() Q_DECL_OVERRIDE; //fom QRunnable

    int getTiming();
    void setTiming(int);

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    bool waitUntilFinished() Q_DECL_OVERRIDE;
    bool finishedWithCriticalError() Q_DECL_OVERRIDE;

    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    variableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;


private:
    bool acquisitionAndTest(float arg_setPointMin, float arg_setPointMax);
    enum eContidion{m_eEqualToSetpoint=0, m_eSuperiorToSetpoint, m_eInferiorToSetPoint};
    IVariable* m_setpoint;
    IVariableInput* m_target;
    IVariable* m_result;
    IVariable* m_waiting;
    eContidion m_condition;
    IVariable* m_errorMargin;
    IVariable* m_timeout;
    CVariableBool* m_criticalError;

};

#endif // CACTIONTEST_H
