#ifndef CACTIONDCENGINE_H
#define CACTIONDCENGINE_H

#include "IAction.h"

class IVariable;
class QTimer;
class CActionDCEngine : public IAction
{
    Q_OBJECT
public:
    CActionDCEngine(const QVariantMap&, QObject *parent);
    ~CActionDCEngine();

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
    void slotTimeout();

private:

    QTimer* m_timer;
    IVariable* m_varPump;
    IVariable* m_varClockwise;
    IVariable* m_varTimeout;

};

#endif // CACTIONDCENGINE_H



