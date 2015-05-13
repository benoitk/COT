#ifndef CCONFIGURATOREXTENSIONSTAB_H
#define CCONFIGURATOREXTENSIONSTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorExtensionsTab;
}
class CConfiguratorExtensionsTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorExtensionsTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorExtensionsTab();
private:
    Ui::CConfiguratorExtensionsTab *ui;
};

#endif // CCONFIGURATOREXTENSIONSTAB_H
