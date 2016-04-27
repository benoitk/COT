#ifndef ICOMMANDS_H
#define ICOMMANDS_H

#include <QObject>
#include <QVariant>

enum commandType{
    type_stop_cycle = 0,
    type_stop_end_cycle,
    type_pause_cycle,
    type_cmd_cycle,
    type_set_remote_control,
    type_get_automate_state,
    type_get_scheduler_state,
    type_get_cycle_state
};

class IVariable;
class ICommand : public QObject
{
    Q_OBJECT
public:
    explicit ICommand(const QVariantMap &mapCmd, QObject *parent);
    ~ICommand();
    QString getName();
    commandType getType();
    virtual QVariantMap serialize();
signals:


public slots:
    virtual bool slotRunCommand(bool arg_externalCmdOnly = false) =0;
    virtual void slotReadInput()=0;
private:
    QString m_name;
    QString m_label;
    commandType m_type;
};

#endif // ICOMMANDS_H