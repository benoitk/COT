#ifndef CACTIONDCENGINE_H
#define CACTIONDCENGINE_H

#include "IAction.h"

class IVariable;
class CActionDCEngine : public IAction
{
    Q_OBJECT
public:
    CActionDCEngine(const QVariantMap&, QObject *parent);
    ~CActionDCEngine();

    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

public slots:
    void slotTimeout();

private:


    IVariable* m_varPump;
    IVariable* m_varClockwise;
    IVariable* m_varTimeout;

};

#endif // CACTIONDCENGINE_H


