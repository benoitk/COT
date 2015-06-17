#ifndef CACTIONCMDRELAY_H
#define CACTIONCMDRELAY_H
#include "IAction.h"

class IVariable;
class CActionCmdRelay : public IAction
{
    Q_OBJECT

public:


    CActionCmdRelay(const QVariantMap&, QObject *parent);
    ~CActionCmdRelay();

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

private:

    IVariable* m_RelayVar;
    bool m_stateOpen;

};

#endif // CACTIONCMDRELAY_H
