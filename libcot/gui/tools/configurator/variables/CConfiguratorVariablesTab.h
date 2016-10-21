#ifndef CCONFIGURATORVARIABLESTAB_H
#define CCONFIGURATORVARIABLESTAB_H

#include "IConfiguratorTab.h"

class ConfiguratorVariablesUIHandler;
class CAutomate;
class CConfiguratorVariablesTab : public IConfiguratorTab
{
    Q_OBJECT

public:
    explicit CConfiguratorVariablesTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);

private slots:
    void slotAddVariable();
    void editVariable(const QString &variableName);

private:
    ConfiguratorVariablesUIHandler *m_ivariableUIHandler;
    CAutomate* m_automate;
};

#endif // CCONFIGURATORVARIABLESTAB_H
