#ifndef CACTIONCALIBRATIONCALCUL_H
#define CACTIONCALIBRATIONCALCUL_H

#include "IAction.h"
#include <QObject>

class CActionCalibrationCalcul : public IAction
{
    Q_OBJECT
public:
    CActionCalibrationCalcul(const QVariantMap&, QObject *parent);
    ~CActionCalibrationCalcul();

    bool runAction(ICycle* arg_stepParent) Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapIVariableParameters() Q_DECL_OVERRIDE;
    QMap<QString, IVariable*> getMapCstParameters() Q_DECL_OVERRIDE;
    void setParameter(const QString& arg_key, IVariable* arg_parameter)Q_DECL_OVERRIDE;
    enumVariableType getWaitedType(const QString& arg_key) Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
private:
    IVariable* m_measure;
    IVariable* m_standardValue;
    IVariable* m_coefCalibration;
    IVariable* m_coefCalibrationNew;
    IVariable* m_default;
    IVariable* m_marginDefault;
    IVariable* m_co2g;
    IVariable* m_vesselVolume;
};

#endif // CACTIONCALIBRATIONCALCUL_H
