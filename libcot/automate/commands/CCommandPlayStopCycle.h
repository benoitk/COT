#ifndef CCOMMANDPLAYSTOPCYCLE_H
#define CCOMMANDPLAYSTOPCYCLE_H

#include "ICommand.h"

class IVariable;
class CCommandPlayStopCycle: public ICommand
{
    Q_OBJECT
public:

    explicit CCommandPlayStopCycle(const QVariantMap &mapAction, QObject *parent);


    bool getStateCommand();
signals:


public slots:
    void slotRunCommand() Q_DECL_OVERRIDE;
    void slotReadInput() Q_DECL_OVERRIDE;

protected:
    IVariable* m_inputVariable;
    bool m_oldValue;

};

#endif // CCOMMANDPLAYSTOPCYCLE_H
