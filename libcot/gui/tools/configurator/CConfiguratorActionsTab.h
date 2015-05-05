#ifndef CCONFIGURATORACTIONSTAB_H
#define CCONFIGURATORACTIONSTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorActionsTab;
}
class CConfiguratorActionsTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorActionsTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorActionsTab();

private slots:
    void addAction();

private:
    Ui::CConfiguratorActionsTab *ui;
};

#endif // CCONFIGURATORACTIONSTAB_H
