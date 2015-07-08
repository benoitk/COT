#ifndef CACTIONCMDREADINPUT_H
#define CACTIONCMDREADINPUT_H

#include "IAction.h"

class IVariable;
class CActionCmdReadInput : public IAction
{
    Q_OBJECT

public:
    CActionCmdReadInput(const QVariantMap&, QObject *parent);
    ~CActionCmdReadInput();

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(QString arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

private:


    IVariable* m_organneVar;
    IVariable* m_variableDestination;
};

#endif // CACTIONCMDREADINPUT_H
