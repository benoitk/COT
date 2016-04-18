#ifndef CCOMMANDUNKNOW_H
#define CCOMMANDUNKNOW_H

#include "ICommand.h"

class IVariable;
class CCommandUnknow: public ICommand
{
    Q_OBJECT
public:

    explicit CCommandUnknow(const QVariantMap &mapCmd, QObject *parent);

signals:


public slots:
    void slotRunCommand() Q_DECL_OVERRIDE;
    void slotReadInput() Q_DECL_OVERRIDE;

};

#endif // CCOMMANDUNKNOW_H
