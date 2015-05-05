#ifndef CONFIGURATORVARIABLESUIHANDLER_H
#define CONFIGURATORVARIABLESUIHANDLER_H

#include "ConfiguratorUIHandler.h"

class ConfiguratorVariablesUIHandler : public ConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorVariablesUIHandler();

};

#endif // CONFIGURATORVARIABLESUIHANDLER_H
