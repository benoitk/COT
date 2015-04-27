#ifndef IVARIABLEMEASURESUIHANDLER_H
#define IVARIABLEMEASURESUIHANDLER_H

#include "IVariableUIHandler.h"

class IVariableMeasuresUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    explicit IVariableMeasuresUIHandler(CScrollableWidget *scrollable, QObject *parent = Q_NULLPTR);

protected:
    virtual QLabel *newLabel(IVariable *ivar) Q_DECL_OVERRIDE;
    virtual QWidget *newEditor(IVariable *ivar) Q_DECL_OVERRIDE;
    virtual QLabel *newUnit(IVariable *ivar) Q_DECL_OVERRIDE;

    virtual int labelColumn() const Q_DECL_OVERRIDE;
    virtual int editorColumn() const Q_DECL_OVERRIDE;
    virtual int unitColumn() const Q_DECL_OVERRIDE;

    virtual void rowInserted(const Row &row) Q_DECL_OVERRIDE;
    virtual void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

private slots:
    void slotButtonMeasureDetailsClicked();
};

#endif // IVARIABLEMEASURESUIHANDLER_H
