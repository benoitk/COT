#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditVariableTab;
}
class IConfiguratorUIHandler;
class IVariable;
class CEditVariableTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditVariableTab(QWidget *parent = Q_NULLPTR);
    ~CEditVariableTab();
    void setVariables(const QString &variableName);
private:
    Ui::CEditVariableTab *ui;
    IConfiguratorUIHandler *m_configuratorUIHandler;
};

#endif // CEDITVARIABLETAB_H
