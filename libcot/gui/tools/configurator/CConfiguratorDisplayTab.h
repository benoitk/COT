#ifndef CCONFIGURATORDISPLAYTAB_H
#define CCONFIGURATORDISPLAYTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorDisplayTab;
}
class CConfiguratorDisplayTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorDisplayTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorDisplayTab();
private:
    Ui::CConfiguratorDisplayTab *ui;
};

#endif // CCONFIGURATORDISPLAYTAB_H
