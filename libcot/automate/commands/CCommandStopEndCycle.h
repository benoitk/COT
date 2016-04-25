#ifndef CCOMMANDSTOPENDCYCLE_H
#define CCOMMANDSTOPENDCYCLE_H

#include "CCommandPlayStopCycle.h"

class CCommandStopEndCycle : public CCommandPlayStopCycle
{
    Q_OBJECT
public:
   explicit CCommandStopEndCycle(const QVariantMap &mapCmd, QObject *parent);

public slots:
    bool slotRunCommand(bool arg_externalCmdOnly = false) Q_DECL_OVERRIDE;
private:
    ICommand* m_cmdPlayStop;

};

#endif // CCOMMANDSTOPENDCYCLE_H
