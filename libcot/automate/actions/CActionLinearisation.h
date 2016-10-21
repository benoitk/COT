#ifndef CACTIONLINEARISATION_H
#define CACTIONLINEARISATION_H

#include <QObject>
#include "IAction.h"
#include "qrunnable.h"

class CVariableCurve;
class CActionLinearisation : public IAction, QRunnable
{
       Q_OBJECT
public:
    CActionLinearisation(const QVariantMap&, CAutomate *parent);


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

private:
    IVariable* m_rawValue;
    IVariable* m_value;
    CVariableCurve* m_curve;

};

#endif // CACTIONLINEARISATION_H
