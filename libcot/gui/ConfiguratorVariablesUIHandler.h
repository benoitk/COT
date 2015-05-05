#ifndef CONFIGURATORVARIABLESUIHANDLER_H
#define CONFIGURATORVARIABLESUIHANDLER_H

#include "cot_global.h"
#include "ConfiguratorUIHandler.h"

class LIBCOT_EXPORT ConfiguratorVariablesUIHandler : public ConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorVariablesUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorVariablesUIHandler();

};

#endif // CONFIGURATORVARIABLESUIHANDLER_H
