#ifndef CCYCLEMAINTENANCE_H
#define CCYCLEMAINTENANCE_H

#include "ICycle.h"

class CCycleMaintenance : public ICycle
{
    Q_OBJECT

public:
    CCycleMaintenance(QObject *parent = Q_NULLPTR);
    CCycleMaintenance(eTypeCycle type, QObject *parent = Q_NULLPTR);
     CCycleMaintenance(const QVariantMap&,QObject *parent);
    ~CCycleMaintenance();

    eTypeCycle getType()const Q_DECL_OVERRIDE;

    QVariantMap serialise() Q_DECL_OVERRIDE;
public slots:
    void slotRunCycle() Q_DECL_OVERRIDE;
    void slotPauseCycle() Q_DECL_OVERRIDE;
    void slotStopCycle() Q_DECL_OVERRIDE;
    void slotUnPauseCycle() Q_DECL_OVERRIDE;
    void slotStopEndCycle() Q_DECL_OVERRIDE;
    void slotGoToEndCycle() Q_DECL_OVERRIDE;
    void slotGoToStepCycle(int) Q_DECL_OVERRIDE;
    void slotGetReadyForPlayNextCycle() Q_DECL_OVERRIDE;
    void slotGetReadyForPlayCycle() Q_DECL_OVERRIDE;

    void slotExecNextStep() Q_DECL_OVERRIDE;


private:




};
#endif // CCYCLEMAINTENANCE_H
