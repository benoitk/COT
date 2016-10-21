#ifndef CACTIONWAITFORACTION_H
#define CACTIONWAITFORACTION_H


#include "IAction.h"

#include "qrunnable.h"

class IVariable;
class CVariableBool;
class IVariableInput;
class CVariableAlarm;
class CActionWaitForAction : public IAction, QRunnable
{
    Q_OBJECT

public:
    CActionWaitForAction(const QVariantMap&, CAutomate *parent);
    ~CActionWaitForAction();


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

public slots:
    void slotActionFinished(IAction*);

private:
    QStringList m_listActionNamesToWait;
    QList<IAction*> m_listActionConnectedToWait;
};

#endif // CACTIONWAITFORACTION_H
