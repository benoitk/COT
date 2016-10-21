#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IConfiguratorEditTab.h"

class CEditVariableTabUIHandler;
class IVariable;
class CAutomate;
class CEditVariableTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditVariableTab(CAutomate* arg_automate, IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditVariableTabUIHandler *m_handler;
    CAutomate* m_automate;
};

#endif // CEDITVARIABLETAB_H
