#ifndef CCONFIGURATORVARIABLESTAB_H
#define CCONFIGURATORVARIABLESTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorVariablesTab;
}
class CConfiguratorVariablesTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorVariablesTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorVariablesTab();
private:
    Ui::CConfiguratorVariablesTab *ui;
};

#endif // CCONFIGURATORVARIABLESTAB_H
