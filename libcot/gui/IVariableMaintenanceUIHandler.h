#ifndef IVARIABLEMAINTENANCEUIHANDLER_H
#define IVARIABLEMAINTENANCEUIHANDLER_H

#include "IVariableUIHandler.h"

class CToolButton;

class IVariableMaintenanceUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IVariableMaintenanceUIHandler(CScrollableWidget *scrollable, QObject *parent = Q_NULLPTR);

    void layout();

protected:
    virtual int columnCount() const Q_DECL_OVERRIDE;
    virtual QWidget *createWidget(int index, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    virtual void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

private:
    QLabel *newLabel(IVariable *ivar);
    CToolButton *newStartEditor(IVariable *ivar);
    CToolButton *newStopEditor(IVariable *ivar);

private slots:
    void slotCycleChanged(const QString &name);
    void slotButtonStartClicked();
    void slotButtonStopClicked();
};

#endif // IVARIABLEMAINTENANCEUIHANDLER_H
