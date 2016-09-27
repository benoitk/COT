#ifndef CACTIONDOUBLETITRATION_H
#define CACTIONDOUBLETITRATION_H


#include <QObject>
#include "IAction.h"
#include "qrunnable.h"

class CVariableBool;
class CVariableOutputBool;
class CVariableOutputInt;
class CVariableInputBool;
class CVariableAlarm;
class CActionDoubleTitration : public IAction, QRunnable
{
    Q_OBJECT
public:
    CActionDoubleTitration(const QVariantMap&, QObject *parent);


    void run() Q_DECL_OVERRIDE; //fom QRunnable

    int getTiming();
    void setTiming(int);

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    bool waitUntilFinished() Q_DECL_OVERRIDE;

    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;

    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;

    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

private:

    IVariable* m_measureCell;

    IVariable* m_timeFirstInflection;
    IVariable* m_timeSecondInflection;

    //Pompe
    CVariableOutputBool* m_alimPump;
    CVariableOutputInt* m_speedPump;
    CVariableOutputBool* m_clockwisePump;
    CVariableOutputBool* m_runOrStopPump;
    CVariableOutputBool* m_OriginReturnPump;
    CVariableInputBool* m_defaultPump;
    CVariableAlarm* m_alarmPump;

    IVariable* m_timeout;
    bool m_waitUntilFinished;
};

#endif // CACTIONDOUBLETITRATION_H
