#ifndef CCYCLEAUTONOME_H
#define CCYCLEAUTONOME_H

//#include "ICycle.h"
#include "CCycleMesure.h"

//class CCycleAutonome : public ICycle
class CCycleAutonome : public CCycleMesure
{
	Q_OBJECT

public:
	CCycleAutonome(QObject *parent);
	CCycleAutonome(QVariantMap);
	CCycleAutonome(QVariantMap, QMap<QString, IAction*>);
	~CCycleAutonome();

/*	void setType(eTypeCycle);
	eTypeCycle getType()const;
	bool isRunning();
	bool isPaused();
	QString getName()const;
	void setName(QString);
	void addAction(IAction*);
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
	eTypeCycle m_typeCycle;
	QString m_name;
	QString m_label;*/
};
#endif // CCYCLEAUTONOME_H
