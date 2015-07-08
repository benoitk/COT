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

protected:
    virtual int columnCount() const Q_DECL_OVERRIDE;
    virtual QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

protected slots:
    void slotRequestVariable();
};

#endif // CEDITACTIONTABUIHANDLER_H
