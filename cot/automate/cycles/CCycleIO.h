#ifndef CCYCLEIO_H
#define CCYCLEIO_H

#include "ICycle.h"

class CCycleIO : public ICycle
{
	Q_OBJECT

public:
	CCycleIO(QObject *parent);
	~CCycleIO();

	eTypeCycle getType()const;
public slots:
	void slotRunCycle();
	void slotPauseCycle();
	void slotStopCycle();
	void addAction(IAction*);


private:
	int m_idCycle;
	
};

#endif // CCYCLEIO_H
