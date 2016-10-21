#ifndef ICOMMANDS_H
#define ICOMMANDS_H

#include <QObject>
#include <QVariant>

enum enumCommandType{
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
class CAutomate;
class ICommand : public QObject
{
    Q_OBJECT
public:
    explicit ICommand(const QVariantMap &mapCmd, CAutomate *parent);
    ~ICommand();
    QString getName();
    enumCommandType getType();
    virtual QVariantMap serialize();
signals:


public slots:
    virtual bool slotRunCommand(bool arg_externalCmdOnly = false) =0;
    virtual void slotReadInput()=0;
private:
    QString m_name;
    QString m_label;
    enumCommandType m_type;

protected:
    CAutomate * m_automate;
};

#endif // ICOMMANDS_H
