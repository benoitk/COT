#ifndef CSTATECYCLERUNNING_H
#define CSTATECYCLERUNNING_H

#include "IState.h"

class IVariable;
class CStateCycleRunning: public IState
{
    Q_OBJECT
public:
    CStateCycleRunning(const QVariantMap &mapSate, QObject *parent);
};

#endif // CSTATECYCLERUNNING_H
