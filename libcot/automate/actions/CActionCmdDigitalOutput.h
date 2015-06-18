#ifndef CACTIONCMDDIGITALOUTPUT_H
#define CACTIONCMDDIGITALOUTPUT_H
#include "IAction.h"

class IVariable;
class CActionCmdDigitalOutput : public IAction
{
    Q_OBJECT

public:


    CActionCmdDigitalOutput(const QVariantMap&, QObject *parent);
    ~CActionCmdDigitalOutput();

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

private:

    IVariable* m_varDigitalOutput;
    bool m_state;

};

#endif // CACTIONCMDDIGITALOUTPUT_H
