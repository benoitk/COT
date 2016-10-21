#ifndef CACTIONFINDCLOSESTFROMREFERENCE_H
#define CACTIONFINDCLOSESTFROMREFERENCE_H

#include "IAction.h"
class IVariable;
class CActionFindClosestFromReference : public IAction
{
    Q_OBJECT
public:
    CActionFindClosestFromReference(const QVariantMap&, CAutomate *parent);
    ~CActionFindClosestFromReference();

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
    IVariable* m_ref;
    IVariable* m_result;
    QList<IVariable*> m_listVar;


};

#endif // CACTIONFINDCLOSESTFROMREFERENCE_H
