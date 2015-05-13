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
    IAction(QObject *parent);
    IAction();
    ~IAction();

    virtual bool runAction()=0;
    virtual QString getName()const=0;
    virtual QString getLabel()const=0;
    virtual void setLabel(const QString&)=0;
    virtual QList<IVariable*> getListParameters()const=0;
    virtual actionType getType()const =0;


};

#endif // IACTION_H
