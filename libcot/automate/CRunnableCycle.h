#ifndef CRUNNABLECYCLE_H
#define CRUNNABLECYCLE_H

#include "ICycle.h"
#include <QRunnable>

class CRunnableCycle : public QRunnable
{

public:
    CRunnableCycle(ICycle *cycle);
    ~CRunnableCycle();

    void run() Q_DECL_OVERRIDE;

private :
    ICycle* m_cycle;
};

#endif // CRUNNABLECYCLE_H
