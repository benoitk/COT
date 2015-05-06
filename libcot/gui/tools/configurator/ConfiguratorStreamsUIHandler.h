#ifndef CONFIGURATORSTREAMSUIHANDLER_H
#define CONFIGURATORSTREAMSUIHANDLER_H

#include "cot_global.h"

#include <ConfiguratorUIHandler.h>

class LIBCOT_EXPORT ConfiguratorStreamsUIHandler : public ConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorStreamsUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorStreamsUIHandler();

    void layout();

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
};

#endif // CONFIGURATORSTREAMSUIHANDLER_H
