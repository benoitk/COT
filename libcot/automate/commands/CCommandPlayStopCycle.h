#ifndef CCOMMANDPLAYSTOPCYCLE_H
#define CCOMMANDPLAYSTOPCYCLE_H

#include "ICommand.h"

class IVariable;
class CCommandPlayStopCycle: public ICommand
{
    Q_OBJECT
public:

    explicit CCommandPlayStopCycle(const QVariantMap &mapAction, QObject *parent);
    void setOtherCmdStop(CCommandPlayStopCycle* arg_cmd);
    bool getStateCommand();
signals:


public slots:
    bool slotRunCommand(bool arg_externalCmdOnly = false) Q_DECL_OVERRIDE;
    void slotReadInput() Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

protected:
    IVariable* m_inputVariable;
    QList<QString> m_listPriorityOrder;
    int m_lastOrderPriority;
    bool m_currentValue;
    CCommandPlayStopCycle* m_cmdStop;

};

#endif // CCOMMANDPLAYSTOPCYCLE_H
