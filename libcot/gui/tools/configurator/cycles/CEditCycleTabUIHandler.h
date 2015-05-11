#ifndef CEDITCYCLETABUIHANDLER_H
#define CEDITCYCLETABUIHANDLER_H

#include "IConfiguratorUIHandler.h"

class ICycle;

typedef QPair<QString, ICycle *> CyclePair; // Stream Name, ICycle

class CEditCycleTabUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit  CEditCycleTabUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CEditCycleTabUIHandler();

    void layout(const CyclePair &cyclePair);
};

#endif // CEDITCYCLETABUIHANDLER_H
