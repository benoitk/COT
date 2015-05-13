#ifndef CEDITVARIABLETABUIHANDLER_H
#define CEDITVARIABLETABUIHANDLER_H

#include "IConfiguratorUIHandler.h"

class IVariable;

class CEditVariableTabUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit  CEditVariableTabUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CEditVariableTabUIHandler();

    void layout(IVariable *ivar);
};

#endif // CEDITVARIABLETABUIHANDLER_H
