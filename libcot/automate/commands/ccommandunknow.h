#ifndef CCOMMANDUNKNOW_H
#define CCOMMANDUNKNOW_H

#include "ICommand.h"

class IVariable;
class CCommandUnknow: public ICommand
{
    Q_OBJECT
public:

    explicit CCommandUnknow(const QVariantMap &mapCmd, CAutomate *parent);
    QVariantMap serialize() Q_DECL_OVERRIDE;
signals:


public slots:
    bool slotRunCommand(bool arg_externalCmdOnly = false) Q_DECL_OVERRIDE;
    void slotReadInput() Q_DECL_OVERRIDE;

};

#endif // CCOMMANDUNKNOW_H
