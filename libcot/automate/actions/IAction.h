#ifndef IACTION_H
#define IACTION_H

#include <QObject>
#include "qmutex.h"
enum actionType{
        type_block = 0,
        type_cmd_pump,
        type_cmd_digital_output,
        type_cmd_read_input,
        type_test,
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

    virtual bool runAction();
    virtual bool waitUnitlFinished();
    virtual bool finishedWithError();
    virtual QList<IVariable*> getListParameters()const=0;
    virtual actionType getType()const =0;
    virtual bool variableUsed(IVariable *)const =0;
    static QString typeToString(actionType type);
    virtual void abortAction();
signals:
    void signalActionFinished(IAction* arg_this);
protected:
    QString m_label;
    QString m_name;

    bool m_abort;
    mutable QMutex m_mutex;
};

#endif // IACTION_H
