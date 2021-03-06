#ifndef ICONFIGURATORUIHANDLER_H
#define ICONFIGURATORUIHANDLER_H

#include "cot_global.h"
#include "IVariableUIHandler.h"
#include "IVariable.h"
#include "ICycle.h"

/**
 * Extends IVariableUIHandler to add support for deletion.
 */
class CAutomate;
class LIBCOT_EXPORT IConfiguratorUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IConfiguratorUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);

protected:
    virtual CToolButton *newDeleteButton(IVariable *ivar);
    virtual void rowAboutToBeDeleted(const Row &row, IVariable *ivar);
    virtual void rowDeleted(const QString &name);
    virtual void applyEditorConstraints(QWidget *editor, IVariable *ivar);

protected slots:
    void slotDeleteClicked();
};

#endif // ICONFIGURATORUIHANDLER_H
