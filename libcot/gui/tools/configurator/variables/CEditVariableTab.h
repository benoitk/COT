#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IConfiguratorEditTab.h"

class CEditVariableTabUIHandler;
class IVariable;

class CEditVariableTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditVariableTab(QWidget *parent = Q_NULLPTR);

    void setVariables(IVariable *ivar);
    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    CEditVariableTabUIHandler *m_configuratorUIHandler;
};

#endif // CEDITVARIABLETAB_H
