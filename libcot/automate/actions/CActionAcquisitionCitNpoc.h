#ifndef CACTIONACQUISITIONCITNPOC_H
#define CACTIONACQUISITIONCITNPOC_H

#include <QObject>
#include "IAction.h"
#include "qrunnable.h"

class CActionAcquisitionCitNpoc : public IAction, QRunnable
{
    Q_OBJECT
public:
    CActionAcquisitionCitNpoc(const QVariantMap&, QObject *parent);


    void run() Q_DECL_OVERRIDE; //fom QRunnable

    int getTiming();
    void setTiming(int);

    bool runAction() Q_DECL_OVERRIDE;
    bool waitUntilFinished() Q_DECL_OVERRIDE;
    bool finishedWithCriticalError() Q_DECL_OVERRIDE;

    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
    bool variableUsed(IVariable *)const Q_DECL_OVERRIDE;


private:

    IVariable* m_measureCell;
    IVariable* m_result;
    IVariable* m_zero;
    IVariable* m_airflow;
    IVariable* m_vesselVolume;
    IVariable* m_coef1;
    IVariable* m_coef2;
    IVariable* m_coef3;
    IVariable* m_coef4;
    IVariable* m_coef5;
    IVariable* m_Offset;
    IVariable* m_CstConversion;

    IVariable* m_timeout;
    bool m_criticalError;
};

#endif // CACTIONACQUISITIONCITNPOC_H
