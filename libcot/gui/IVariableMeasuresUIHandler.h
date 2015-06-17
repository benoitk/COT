#ifndef IVARIABLEMEASURESUIHANDLER_H
#define IVARIABLEMEASURESUIHANDLER_H

#include "IVariableUIHandler.h"
#include <CAutomate.h>

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
    QWidget *newDetailsButton(IVariable *ivar);
    QLabel *newLabel(IVariable *ivar);
    QLabel *newValueLabel(IVariable *ivar);
    QLabel *newErrorLabel(IVariable *ivar);
    QString textForStreamState(CAutomate::eStateStream state) const;

private slots:
    void slotButtonMeasureDetailsClicked();
    void slotUpdateStateStream(const QString& arg_streamName, CAutomate::eStateStream state);
};

#endif // IVARIABLEMEASURESUIHANDLER_H
