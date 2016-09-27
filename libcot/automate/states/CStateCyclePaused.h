#ifndef CSTATECYCLEPAUSED_H
#define CSTATECYCLEPAUSED_H

#include "IState.h"

class IVariable;
class CStateCyclePaused: public IState
{
    Q_OBJECT
public:
    CStateCyclePaused(const QVariantMap &mapSate, QObject *parent);
};

#endif // CSTATECYCLEPAUSED_H
