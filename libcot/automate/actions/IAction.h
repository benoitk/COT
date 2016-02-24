#ifndef IACTION_H
#define IACTION_H

#include "IVariable.h"

#include <QObject>
#include "qmutex.h"
enum actionType{
    type_block = 0,
    type_cmd_pump,
    type_cmd_420,
    type_cmd_digital_output,
    type_rewrite_output,
    type_cmd_dc_engine,
    type_cmd_read_input,
    type_test,
    type_acquisition_cit_npoc,
    type_slope,
    type_action_unknow

};

class ICycle;
class IAction : public QObject
{
    Q_OBJECT

public:
    IAction(const QVariantMap &mapAction, QObject *parent);

    ~IAction();

    virtual QString getName()const;
    virtual QString getLabel()const;
    virtual void setLabel(const QString&);

    virtual bool runAction(ICycle* arg_stepParent);
    virtual bool waitUntilFinished();
    virtual QList<IVariable*> getListParameters()const=0;
    virtual actionType getType()const =0;
    virtual bool variableUsed(IVariable *)const =0;
    virtual QMap<QString, IVariable*> getMapIVariableParameters()=0;
    virtual QMap<QString, IVariable*> getMapCstParameters()=0;
    virtual void setParameter(const QString& arg_key, IVariable* arg_parameter)=0;
    virtual enumVariableType getWaitedType(const QString& arg_key)=0;
    static QString typeToString(actionType type);
    virtual void abortAction();
    virtual QVariantMap serialize();
signals:
    void signalActionFinished(IAction* arg_this);


private:
      ICycle* m_stepParent;

protected:
      ICycle* getStepParent();
      virtual void updateActionInfos(QString arg_actionInfo, ICycle* arg_stepParent);

    QString m_label;
    QString m_name;
    bool m_abort;
    mutable QMutex m_mutex;
};

#endif // IACTION_H
