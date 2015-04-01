#ifndef CCYCLEPAUSE_H
#define CCYCLEPAUSE_H

#include "ICycle.h"
#include "qthread.h"
class QTimer;
class CCyclePause : public ICycle
{
	Q_OBJECT

public: //acces multithread possible sur tout les get, penser au mutex sur tous les accès aux variables.
	CCyclePause(QObject *parent);
	CCyclePause(QVariantMap);
    CCyclePause(QObject* parent, int temps);
    CCyclePause(int temps);
	~CCyclePause();

	void addAction(int, IAction*);
	eTypeCycle getType()const;
	void setType(eTypeCycle);
	QString getLbl()const;
	void setLbl(QString);
	QString getName()const;
	void setName(QString);

	bool isRunning();
	bool isPaused();

public slots:
	void slotRunCycle();
	void slotPauseCycle();
	void slotUnPauseCycle();
	void slotStopCycle();
	void slotStopEndCycle();
	void slotGoToEndCycle();
	void slotGoToStepCycle(int);
	void slotGetReadyForPlayNextCycle();
	void slotGetReadyForPlayCycle();

	void slotExecNextStep();

	
private : 

	void initTimer();

	QTimer* m_timer;
	int m_iTimer;
	int m_iTempsCycle;
	QString m_name;
	QString m_label;

	QThread m_thread;
	
};

#endif // CCYCLEPAUSE_H
