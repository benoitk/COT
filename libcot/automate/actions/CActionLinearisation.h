#ifndef CACTIONLINEARISATION_H
#define CACTIONLINEARISATION_H

#include <QObject>
#include "IAction.h"
#include "qrunnable.h"

class CVariableBool;
class CActionLinearisation : public IAction, QRunnable
{
       Q_OBJECT
public:
    CActionLinearisation(const QVariantMap&, QObject *parent);


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




    IVariable* m_zero;

    IVariable* m_coef1;
    IVariable* m_coef2;
    IVariable* m_coef3;
    IVariable* m_coef4;
    IVariable* m_coef5;
    IVariable* m_coefCorrection;
    IVariable* m_coefCourbe;
    IVariable* m_Offset;





    CVariableBool* m_derivativeCalcul;
    bool m_waitUntilFinished;
};

#endif // CACTIONLINEARISATION_H