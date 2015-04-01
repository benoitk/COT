#include "CControlerCycle.h"

CControlerCycle::CControlerCycle(QObject *parent, ICycle* cycle)
	: QObject(parent)
{
	connect(this, &CControlerCycle::signalRunCycle, cycle, &ICycle::slotRunCycle);
	connect(this, &CControlerCycle::signalPauseCycle, cycle, &ICycle::slotPauseCycle);
	connect(this, &CControlerCycle::signalStopCycle, cycle, &ICycle::slotStopCycle);
}

CControlerCycle::~CControlerCycle()
{
	disconnect(this, 0,0,0);
}
