#ifndef CCONFIGURATORVARIABLESTAB_H
#define CCONFIGURATORVARIABLESTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorVariablesUIHandler;

class CConfiguratorVariablesTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorVariablesTab(QWidget *parent = Q_NULLPTR);

private slots:
    void slotAddVariable();
    void editVariable(const QString &variableName);
    void slotUpdateLayout();

private:
    ConfiguratorVariablesUIHandler *m_ivariableUIHandler;
};

#endif // CCONFIGURATORVARIABLESTAB_H
