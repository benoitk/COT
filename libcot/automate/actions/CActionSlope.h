#ifndef CACTIONSLOPE_H
#define CACTIONSLOPE_H

#include "IAction.h"
#include "qrunnable.h"

class IVariable;
class CActionSlope : public IAction, QRunnable
{
    Q_OBJECT
public:
    CActionSlope(const QVariantMap&, QObject *parent);
    ~CActionSlope();

    void run() Q_DECL_OVERRIDE; //fom QRunnable
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
    IVariable* m_startSetpoint;
    IVariable* m_inibitedAlarm;
    IVariable* m_setpoint;
    IVariable* m_duration;
    IVariable* m_nbSection;

};

#endif // CACTIONSLOPE_H


