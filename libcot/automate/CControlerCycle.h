#ifndef CCONTROLERCYCLE_H
#define CCONTROLERCYCLE_H

#include <QObject>
#include "ICycle.h"
class CControlerCycle : public QObject
{
	Q_OBJECT

public:
	CControlerCycle(QObject *parent, ICycle* cycle);
	~CControlerCycle();

signals:
	void signalRunCycle();
	void signalPauseCycle();
	void signalStopCycle();
};

#endif // CCONTROLERCYCLE_H
