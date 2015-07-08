#ifndef CACTIONREWRITEOUTPUT_H
#define CACTIONREWRITEOUTPUT_H

#include "IAction.h"
class IVariable;
class CActionRewriteOutput : public IAction
{
    Q_OBJECT
public:
    CActionRewriteOutput(const QVariantMap&, QObject *parent);
    ~CActionRewriteOutput();


    bool runAction() Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(QString arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;
private:

    IVariable* m_varDigitalOutput;
};

#endif // CACTIONREWRITEOUTPUT_H
