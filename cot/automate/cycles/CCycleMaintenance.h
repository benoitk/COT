#ifndef CCYCLEMAINTENANCE_H
#define CCYCLEMAINTENANCE_H

#include "ICycle.h"

class CCycleMaintenance : public ICycle
{
	Q_OBJECT

public:
	CCycleMaintenance(QObject *parent);
	CCycleMaintenance(QObject *parent, eTypeCycle);
	~CCycleMaintenance();

	void setType(eTypeCycle);
	eTypeCycle getType()const;
	void addAction(IAction*);
	QString getName()const;
	void setName(QString);
	bool isRunning();
	bool isPaused();
	QString getLbl()const;
	void setLbl(QString);
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
	int m_idCycle;
	QString m_name;
	QString m_label;
	eTypeCycle m_typeCycle;
};
#endif // CCYCLEMAINTENANCE_H
