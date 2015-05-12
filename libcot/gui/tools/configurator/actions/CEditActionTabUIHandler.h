#ifndef CEDITACTIONTABUIHANDLER_H
#define CEDITACTIONTABUIHANDLER_H

#include "IConfiguratorUIHandler.h"

class IAction;

class CEditActionTabUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit  CEditActionTabUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CEditActionTabUIHandler();

    void layout(IAction *action);
};

#endif // CEDITACTIONTABUIHANDLER_H
