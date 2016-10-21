#ifndef CEDITVARIABLETABUIHANDLER_H
#define CEDITVARIABLETABUIHANDLER_H

#include "IConfiguratorUIHandler.h"

class IVariable;

class CEditVariableTabUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit  CEditVariableTabUIHandler(CAutomate* arg_automate,CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~CEditVariableTabUIHandler();

    void layout(IVariable *ivar);

protected:
    virtual void rowChanged(const Row &row, IVariable *ivar);
    CAutomate* m_automate;
};

#endif // CEDITVARIABLETABUIHANDLER_H
