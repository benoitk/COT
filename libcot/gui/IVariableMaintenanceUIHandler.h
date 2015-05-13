#ifndef IVARIABLEMAINTENANCEUIHANDLER_H
#define IVARIABLEMAINTENANCEUIHANDLER_H

#include "IVariableUIHandler.h"

class CToolButton;

class IVariableMaintenanceUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IVariableMaintenanceUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);

    void layout();

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int index, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

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
