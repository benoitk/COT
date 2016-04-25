#ifndef CCOMMANDSTOPENDCYCLE_H
#define CCOMMANDSTOPENDCYCLE_H

#include "CCommandPlayStopCycle.h"

class CCommandStopEndCycle : public CCommandPlayStopCycle
{
    Q_OBJECT
public:
   explicit CCommandStopEndCycle(const QVariantMap &mapCmd, QObject *parent);

public slots:
    bool slotRunCommand(IVariable* = Q_NULLPTR) Q_DECL_OVERRIDE;

};

#endif // CCOMMANDSTOPENDCYCLE_H
