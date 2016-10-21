#ifndef CACTIONACQUISITIONCITNPOC_H
#define CACTIONACQUISITIONCITNPOC_H

#include <QObject>
#include "IAction.h"
#include "qrunnable.h"

class CVariableBool;
class CActionAcquisitionCitNpoc : public IAction, QRunnable
{
    Q_OBJECT
public:
    CActionAcquisitionCitNpoc(const QVariantMap&, CAutomate *parent);


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

    IVariable* m_measureCell;
    IVariable* m_co2g;
    IVariable* m_result;
    IVariable* m_zero;
    IVariable* m_offsetCo2g;
    QList<IVariable*> m_listAirflows;
    IVariable* m_vesselVolume;
    IVariable* m_coef1;
    IVariable* m_coef2;
    IVariable* m_coef3;
    IVariable* m_coef4;
    IVariable* m_coef5;
    IVariable* m_coefCorrection;
    IVariable* m_coefCourbe;
    IVariable* m_Offset;
    IVariable* m_CstConversion;
    IVariable* m_derivativeIntervalTx;
    IVariable* m_derivativeThresold;
    IVariable* m_linearisationCurve;

    IVariable* m_timeout;
    CVariableBool* m_derivativeCalcul;
    bool m_waitUntilFinished;
};

#endif // CACTIONACQUISITIONCITNPOC_H
