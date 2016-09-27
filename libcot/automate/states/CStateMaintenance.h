#ifndef CSTATEMAINTENANCE_H
#define CSTATEMAINTENANCE_H

#include "IState.h"

class IVariable;
class CStateMaintenance : public IState
{
    Q_OBJECT
public:
    CStateMaintenance(const QVariantMap &mapSate, QObject *parent);
};

#endif // CSTATEMAINTENANCE_H
