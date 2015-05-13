#ifndef CCONFIGURATORVARIABLESTAB_H
#define CCONFIGURATORVARIABLESTAB_H

#include "IConfiguratorTab.h"
namespace Ui {
class CConfiguratorVariablesTab;
}
class ConfiguratorVariablesUIHandler;
class CConfiguratorVariablesTab : public IConfiguratorTab
{
    Q_OBJECT
public:
    explicit CConfiguratorVariablesTab(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorVariablesTab();

private slots:
    void slotAddVariable();
    void editVariable(const QString &variableName);

    void slotUpdateLayout();
private:
    Ui::CConfiguratorVariablesTab *ui;
    ConfiguratorVariablesUIHandler *m_ivariableUIHandler;
};

#endif // CCONFIGURATORVARIABLESTAB_H
