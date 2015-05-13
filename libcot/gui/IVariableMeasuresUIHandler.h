#ifndef IVARIABLEMEASURESUIHANDLER_H
#define IVARIABLEMEASURESUIHANDLER_H

#include "IVariableUIHandler.h"

class IVariableMeasuresUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IVariableMeasuresUIHandler(CScrollableWidget *scrollable = Q_NULLPTR, QObject *parent = Q_NULLPTR);

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int index, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

private:
    QWidget *newEditor(IVariable *ivar);
    QLabel *newLabel(IVariable *ivar);
    QLabel *newUnit(IVariable *ivar);

private slots:
    void slotButtonMeasureDetailsClicked();
};

#endif // IVARIABLEMEASURESUIHANDLER_H
