#ifndef CACTIONOFFSET_H
#define CACTIONOFFSET_H

#include "IAction.h"

class IVariable;
class CActionSum: public IAction
{
    Q_OBJECT
public:
    CActionSum(const QVariantMap&, QObject *parent);

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
public slots:

private:

    QList<IVariable*> m_listVar;
    IVariable* m_result;

};

#endif // CACTIONOFFSET_H



