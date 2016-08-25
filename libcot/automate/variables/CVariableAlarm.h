#ifndef CVARIABLEALARM_H
#define CVARIABLEALARM_H

#include "CVariableOutputBool.h"
#include "CVariableBool.h"

#include <qobject.h>

enum enumAlarmType{e_warning_do_nothing, e_not_critical_error_skip_cycle_try_again, e_critical_error_stop_cycle};


class CVariableAlarm : public CVariableOutputBool
{
    Q_OBJECT
public:

    CVariableAlarm(QObject *parent = Q_NULLPTR);
    CVariableAlarm(const QMap<QString, QVariant> &mapVar);
    ~CVariableAlarm();

    //IVariableInput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    void setValue(bool arg_value);
    using CVariableOutputBool::setValue;
    void setToBindedValue(const QVariant & value) Q_DECL_OVERRIDE;

    enumAlarmType getAlarmType();
    bool haveToStopAfterToMuchSkip();

    void setInhibited(bool arg = true);
    void deconnectFromAutomate();
    void connectFromAutomate();

public slots:
    void slotAcquit();
signals:
    void signalNewAlarm(CVariableAlarm*);
    void signalAquitedAlarm(CVariableAlarm*);
    void signalStillInAlarm(CVariableAlarm*);
private:
    void setValue(bool arg_value, bool arg_forceAcquit);
    enumAlarmType m_alarmType;
    bool m_autoAcquit;
    int m_countUntilSetAlarm;
    int m_numUntilSetAlarm;
    int m_nbSkipBeforeStopCycle;
    int m_countSkipBeforeStopCycle;
    bool m_inhibited;
};

#endif
