#ifndef CCYCLEIO_H
#define CCYCLEIO_H

#include "ICycle.h"

class CCycleIO : public ICycle
{
	Q_OBJECT

public:
	CCycleIO(QObject *parent);
	~CCycleIO();

    eTypeCycle getType()const Q_DECL_OVERRIDE;
    int getCurrentStepIndex() const Q_DECL_OVERRIDE;

public slots:
    void slotRunCycle() Q_DECL_OVERRIDE;
    void slotPauseCycle() Q_DECL_OVERRIDE;
    void slotStopCycle() Q_DECL_OVERRIDE;
    void addAction(int, IAction*) Q_DECL_OVERRIDE;


private:
	int m_idCycle;
	
};

#endif // CCYCLEIO_H
