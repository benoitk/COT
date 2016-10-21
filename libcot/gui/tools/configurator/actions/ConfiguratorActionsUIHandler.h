#ifndef CONFIGURATORACTIONSUIHANDLER_H
#define CONFIGURATORACTIONSUIHANDLER_H

#include <IConfiguratorUIHandler.h>

class CPushButton;

class LIBCOT_EXPORT ConfiguratorActionsUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    explicit ConfiguratorActionsUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorActionsUIHandler();

    void layout();

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowDeleted(const QString &name) Q_DECL_OVERRIDE;
    IVariable *getVariable(const QString &name) const Q_DECL_OVERRIDE;

private slots:
    void slotEditClicked();

private:
    QHash<QString, IVariable *> m_internalVariables;
    CAutomate* m_automate;
};

#endif // CONFIGURATORACTIONSUIHANDLER_H
