#ifndef CSTATESTOPPED_H
#define CSTATESTOPPED_H

#include "IState.h"

class IVariable;
class CStateStopped: public IState
{
    Q_OBJECT

public:
    CStateStopped(const QVariantMap &mapSate, QObject *parent);

public slots:
   void slotSetStateVaraibles() Q_DECL_OVERRIDE;
};
#endif // CSTATESTOPPED_H
