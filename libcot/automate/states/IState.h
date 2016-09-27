#ifndef ISTATE_H
#define ISTATE_H

#include <QObject>
#include <QList>

#include "CAutomate.h"

enum enumStateType{
    e_state_type_cycle_stopped = 0,
    e_state_type_cycle_paused,
    e_state_type_cycle_running,
    e_state_type_blank_cycle_running,
    e_state_type_in_maintenance,
    e_state_type_unknow
};
class IVariable;
class IState:public  QObject
{
    Q_OBJECT
public:
    IState(const QVariantMap &mapCmd, QObject *parent);

    QString getName();
    enumStateType getType();
    virtual QVariantMap serialize();
signals:
    void signalStateChanged();

public slots:
    virtual void slotSetStateVaraibles()=0;
protected:
    void setStateVariables(bool arg_State);

    QString m_name;
    QString m_label;
    enumStateType m_type;
    QList<IVariable*> m_listVariablesToSet;
};

#endif // ISTATE_H
