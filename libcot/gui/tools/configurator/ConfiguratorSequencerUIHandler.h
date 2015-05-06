#ifndef CONFIGURATORSEQUENCERUIHANDLER_H
#define CONFIGURATORSEQUENCERUIHANDLER_H

#include <ConfiguratorUIHandler.h>

class ConfiguratorSequencerUIHandler : public ConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorSequencerUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorSequencerUIHandler();
    void layout();

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
};

#endif // CONFIGURATORSEQUENCERUIHANDLER_H
