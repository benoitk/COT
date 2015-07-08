#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IConfiguratorEditTab.h"

class CEditVariableTabUIHandler;
class IVariable;

class CEditVariableTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditVariableTab(IVariable *ivar, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditVariableTabUIHandler *m_handler;
};

#endif // CEDITVARIABLETAB_H
