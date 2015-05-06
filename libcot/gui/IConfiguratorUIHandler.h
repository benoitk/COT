#ifndef ICONFIGURATORUIHANDLER_H
#define ICONFIGURATORUIHANDLER_H

#include "cot_global.h"
#include "IVariableUIHandler.h"
#include "IVariable.h"
#include "ICycle.h"

class LIBCOT_EXPORT IConfiguratorUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IConfiguratorUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);

protected:
    virtual QWidget *newDeleteButton(IVariable *ivar);
    virtual void rowAboutToBeDeleted(const Row &row, IVariable *ivar);

protected slots:
    void slotDeleteClicked();
};

#endif // ICONFIGURATORUIHANDLER_H
