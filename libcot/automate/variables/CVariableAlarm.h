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
    void setValue(bool);
    using CVariableOutputBool::setValue;
    void writeValue() Q_DECL_OVERRIDE;

    enumAlarmType getAlarmType();

signals:
    void signalNewAlarm(CVariableAlarm*);
    void signalCancelAlarm(CVariableAlarm*);

private:
    bool m_passive;
    enumAlarmType m_alarmType;
};

#endif
