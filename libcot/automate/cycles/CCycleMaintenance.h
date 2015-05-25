#ifndef CCYCLEMAINTENANCE_H
#define CCYCLEMAINTENANCE_H

#include "ICycle.h"

class CCycleMaintenance : public ICycle
{
    Q_OBJECT

public:
    CCycleMaintenance(QObject *parent = Q_NULLPTR);
    CCycleMaintenance(eTypeCycle type, QObject *parent = Q_NULLPTR);
    ~CCycleMaintenance();

    void setType(eTypeCycle) Q_DECL_OVERRIDE;
    eTypeCycle getType()const Q_DECL_OVERRIDE;
    void addAction(float arg_step, IAction* action) Q_DECL_OVERRIDE;
    void removeAction(IAction*)Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString&) Q_DECL_OVERRIDE;
    bool isRunning() Q_DECL_OVERRIDE;
    bool isPaused() Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLbl(const QString&) Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    CVariableStream* getRelatedStream()const Q_DECL_OVERRIDE;
    void setRelatedStreamName(const QString &name) Q_DECL_OVERRIDE;
    QList<CStep*> getListSteps()const Q_DECL_OVERRIDE;
    CStep* getStepStop()const Q_DECL_OVERRIDE;
    int getCurrentStepIndex() const Q_DECL_OVERRIDE;
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
    int m_idCycle;
    QString m_name;
    QString m_label;
    QString m_streamName;
    eTypeCycle m_typeCycle;
    CStep* m_stepStop;
    QList<CStep*> m_listSteps;

};
#endif // CCYCLEMAINTENANCE_H
