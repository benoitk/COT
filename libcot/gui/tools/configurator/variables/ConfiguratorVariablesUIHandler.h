#ifndef CONFIGURATORVARIABLESUIHANDLER_H
#define CONFIGURATORVARIABLESUIHANDLER_H

#include "cot_global.h"
#include "IConfiguratorUIHandler.h"

class CPushButton;
class CAutomate;
class LIBCOT_EXPORT ConfiguratorVariablesUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT
public:
    explicit ConfiguratorVariablesUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);
    ~ConfiguratorVariablesUIHandler();

    IVariable *getVariable(const QString &name) const Q_DECL_OVERRIDE;

public slots:
    void layout();

signals:
    void editVariable(const QString &varname);

protected:
    QHash<QString, IVariable *> m_internalVariables;

    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowDeleted(const QString &name) Q_DECL_OVERRIDE;

private slots:
    void slotEditClicked();

private:
    CPushButton *newButton(IVariable *ivar);
    IVariable *getStreamOrMeasure(IVariable *ivar) const;
    CAutomate* m_automate;
};

#endif // CONFIGURATORVARIABLESUIHANDLER_H
