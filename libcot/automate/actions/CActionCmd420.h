#ifndef CACTIONCMD420_H
#define CACTIONCMD420_H

#include "IAction.h"
class IVariable;
class CVariableOutputInt;
class CActionCmd420: public IAction
{
    Q_OBJECT

public:

    CActionCmd420(const QVariantMap &, QObject *parent);

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
private:

    IVariable* m_inputVar;
    IVariable* m_inputVarMin;
    IVariable* m_inputVarMax;
    IVariable* m_minAdjustement;
    IVariable* m_maxAdjustement;
    CVariableOutputInt* m_outputVar;
};

#endif // CACTIONCMD420_H
