#ifndef CACTIONCMDRELAY_H
#define CACTIONCMDRELAY_H
#include "IAction.h"

class IVariable;
class CActionCmdRelay : public IAction
{
    Q_OBJECT

public:

    CActionCmdRelay(QObject *parent);
    CActionCmdRelay(const QVariantMap&);
    CActionCmdRelay();
    ~CActionCmdRelay();

    int getTiming();    
    void setTiming(int);
    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLabel(const QString&) Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
private:

    QString m_label;
    IVariable* m_RelayVar;
    QString m_name;
    
};

#endif // CACTIONCMDRELAY_H
