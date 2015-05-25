#ifndef CCYCLEMESURE_H
#define CCYCLEMESURE_H

#include "ICycle.h"
#include <qlinkedlist.h>

#include "qthread.h"

class CLinkAction;
class QTimer;
class CCycleMesure : public ICycle
{
    Q_OBJECT

public:
    CCycleMesure(QObject *parent = Q_NULLPTR);
    CCycleMesure(const QVariantMap&);
    ~CCycleMesure();

    void setType(eTypeCycle) Q_DECL_OVERRIDE;
    eTypeCycle getType()const Q_DECL_OVERRIDE;
    void addAction(float, IAction*) Q_DECL_OVERRIDE;
    void removeAction(IAction*)Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString &) Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLbl(const QString&) Q_DECL_OVERRIDE;
    bool isRunning() Q_DECL_OVERRIDE;
    bool isPaused() Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
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
    void initTimer();
    int m_idCycle;
    QString m_name;
    eTypeCycle m_typeCycle;

    //QTimer* m_timer;
    int m_iTimer;
    QString m_label;
    int m_timeout;
    QThread m_thread;
    QString m_streamName;

    CStep* m_stepStop;
    QList<CStep*> m_listSteps;
    QList<CStep*>::iterator m_itListStepsPasEnCours;
};
#endif // CCYCLEMESURE_H
