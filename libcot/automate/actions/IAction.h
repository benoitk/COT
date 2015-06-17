#ifndef IACTION_H
#define IACTION_H

#include <QObject>

enum actionType{
        type_block = 0,
        type_cmd_pump,
        type_cmd_relay,
        type_cmd_read_input,
        type_action_unknow

};

class IVariable;
class IAction : public QObject
{
    Q_OBJECT

public:
    IAction(const QVariantMap &mapAction, QObject *parent);

    IAction();
    ~IAction();

    virtual QString getName()const;
    virtual QString getLabel()const;
    virtual void setLabel(const QString&);

    virtual bool runAction()=0;   
    virtual QList<IVariable*> getListParameters()const=0;
    virtual actionType getType()const =0;
    virtual bool variableUsed(IVariable *)const =0;
    static QString typeToString(actionType type);

signals:
    void finish(IAction* arg_this);

protected:
    QString m_label;
    QString m_name;

};

#endif // IACTION_H
