#ifndef CSTATEUNKNOW_H
#define CSTATEUNKNOW_H

#include "IState.h"

class IVariable;
class CStateUnknow: public IState
{
    Q_OBJECT
public:
    CStateUnknow(const QVariantMap &mapSate, QObject *parent);
};

#endif // CSTATEUNKNOW_H
