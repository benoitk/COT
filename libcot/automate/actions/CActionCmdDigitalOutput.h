#ifndef CACTIONCMDDIGITALOUTPUT_H
#define CACTIONCMDDIGITALOUTPUT_H
#include "IAction.h"

class IVariable;
class CVariableBool;
class CActionCmdDigitalOutput : public IAction
{
    Q_OBJECT

public:


    CActionCmdDigitalOutput(const QVariantMap&, QObject *parent);
    ~CActionCmdDigitalOutput();


    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    variableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
private:

    IVariable* m_varDigitalOutput;
    CVariableBool* m_state;

};

#endif // CACTIONCMDDIGITALOUTPUT_H
