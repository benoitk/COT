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
    bool slotRunCommand(IVariable* = Q_NULLPTR) Q_DECL_OVERRIDE;
    void slotReadInput() Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;

protected:
    IVariable* m_inputVariable;
    QList<QString> m_listPriorityOrder;
    int m_lastOrderPriority;
    bool m_oldValue;

};

#endif // CCOMMANDPLAYSTOPCYCLE_H
