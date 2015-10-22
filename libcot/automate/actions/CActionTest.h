#ifndef CACTIONTEST_H
#define CACTIONTEST_H

#include "IAction.h"

#include "qrunnable.h"

class IVariable;
class CVariableBool;
class IVariableInput;
class CVariableAlarm;
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


    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

private:
    bool acquisitionAndTest(float arg_setPointMin, float arg_setPointMax);
    enum eContidion{m_eEqualToSetpoint=0, m_eSuperiorToSetpoint, m_eInferiorToSetPoint};
    IVariable* m_setpoint;
    IVariable* m_target;
    CVariableAlarm* m_result;
    IVariable* m_waiting;
    eContidion m_condition;
    IVariable* m_errorMargin;
    IVariable* m_timeout;
    IVariable* m_nbMinimumTry;

};

#endif // CACTIONTEST_H
