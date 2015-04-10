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
	CCycleMesure(QObject *parent);
    CCycleMesure(const QVariantMap&);
    CCycleMesure(const QVariantMap&, const QMap<QString, IAction*>&);
	CCycleMesure();
	~CCycleMesure();

    void setType(eTypeCycle) Q_DECL_OVERRIDE;
    eTypeCycle getType()const Q_DECL_OVERRIDE;
    void addAction(int, IAction*) Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    void setName(QString) Q_DECL_OVERRIDE;
    QString getLbl()const Q_DECL_OVERRIDE;
    void setLbl(const QString&) Q_DECL_OVERRIDE;
    bool isRunning() Q_DECL_OVERRIDE;
    bool isPaused() Q_DECL_OVERRIDE;

    bool isStreamRelated()const Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    QList<CStep*> getListSteps()const Q_DECL_OVERRIDE;
    CStep* getStepStop()const Q_DECL_OVERRIDE;

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
	QLinkedList<CLinkAction*> m_ListActions;
	QLinkedList<CLinkAction*>::iterator m_itListActionsPasEnCours;

	QTimer* m_timer;
	int m_iTimer;
	QString m_label;
	int m_periode;

	QThread m_thread;

	CStep* m_stepStop;
	QList<CStep*> m_listSteps;
};
#endif // CCYCLEMESURE_H
