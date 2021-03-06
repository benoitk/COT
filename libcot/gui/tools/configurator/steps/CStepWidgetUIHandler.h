#ifndef CSTEPWIDGETUIHANDLER_H
#define CSTEPWIDGETUIHANDLER_H

#include "IConfiguratorUIHandler.h"


class CStepWidgetUIHandler : public IConfiguratorUIHandler
{
    Q_OBJECT

public:
    CStepWidgetUIHandler(CAutomate* arg_automate, CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);

    void layout(CStep *step);
    void layout(const QStringList &actions);

protected:
    virtual int columnCount() const Q_DECL_OVERRIDE;
    virtual QWidget *createWidget(int column, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowAboutToBeDeleted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowDeleted(const QString &name) Q_DECL_OVERRIDE;
    CAutomate* m_automate;
};

#endif // CSTEPWIDGETUIHANDLER_H
