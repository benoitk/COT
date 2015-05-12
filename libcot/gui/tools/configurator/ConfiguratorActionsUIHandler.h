#ifndef CONFIGURATORACTIONSUIHANDLER_H
#define CONFIGURATORACTIONSUIHANDLER_H

#include <IConfiguratorUIHandler.h>
#include "cot_global.h"

class LIBCOT_EXPORT ConfiguratorActionsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorActionsUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorActionsUIHandler();
    void layout();

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
};

#endif // CONFIGURATORACTIONSUIHANDLER_H
