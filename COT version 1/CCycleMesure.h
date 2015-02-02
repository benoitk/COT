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
	CCycleMesure(QVariantMap);
	CCycleMesure(QVariantMap, QMap<QString, IAction*>);
	CCycleMesure();
	~CCycleMesure();

	void setType(eTypeCycle);
	eTypeCycle getType()const;
	void addAction(int, IAction*);
	QString getName()const;
	void setName(QString);
	QString getLbl()const;
	void setLbl(QString);
	bool isRunning();
	bool isPaused();

public slots:
	void slotRunCycle();
	void slotPauseCycle();
	void slotStopCycle();
	void slotUnPauseCycle();
	void slotStopEndCycle();
	void slotGoToEndCycle();
	void slotGoToStepCycle(int);
	void slotGetReadyForPlayNextCycle();
	void slotGetReadyForPlayCycle();
	
	void slotExecNextStep();

private:
	void initTimer();
	int m_idCycle;
	QString m_name;
	eTypeCycle m_typeCycle;
	QLinkedList<CLinkAction*> m_ListAction;
	QLinkedList<CLinkAction*>::iterator m_itListActionPasEnCours;

	QTimer* m_timer;
	int m_iTimer;
	QString m_label;

	QThread m_thread;
};
#endif // CCYCLEMESURE_H
