#ifndef CACTIONUNKNOW_H
#define CACTIONUNKNOW_H

#include "IAction.h"

class CActionUnknow : public IAction
{
    Q_OBJECT

public:

    CActionUnknow(const QVariantMap &mapAction, QObject *parent);
    ~CActionUnknow();

    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

    virtual QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    virtual QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
private:

};

#endif // CACTIONUNKNOW_H
