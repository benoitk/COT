#ifndef CEDITOUTBINDSUIHANDLER_H
#define CEDITOUTBINDSUIHANDLER_H

#include <IConfiguratorUIHandler.h>

class CEditOutBindsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit CEditOutBindsUIHandler(CScrollableWidget *scrollable, QObject *parent);
    ~CEditOutBindsUIHandler();

    void layout(IVariable *ivar);
    void layout(const QStringList &variableNames);

    QStringList getBindingNames() const;

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowDeleted(const QString &name) Q_DECL_OVERRIDE;
};

#endif // CEDITOUTBINDSUIHANDLER_H
