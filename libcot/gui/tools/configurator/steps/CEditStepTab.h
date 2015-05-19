#ifndef CEDITSTEPTAB_H
#define CEDITSTEPTAB_H

#include "IConfiguratorEditTab.h"

class CStep;
class IConfiguratorUIHandler;
class CVariableCStepDescriber;

class CEditStepTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditStepTab(CStep *step, QWidget *parent = Q_NULLPTR);
    ~CEditStepTab();

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    IConfiguratorUIHandler *m_handler;
    CVariableCStepDescriber *m_describer;
};

#endif // CEDITSTEPTAB_H
