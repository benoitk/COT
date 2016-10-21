#ifndef IVARIABLEMEASURESUIHANDLER_H
#define IVARIABLEMEASURESUIHANDLER_H

#include "IVariableUIHandler.h"
#include <CAutomate.h>

class IVariableMeasuresUIHandler : public IVariableUIHandler
{
    Q_OBJECT

public:
    enum Flag
    {
        NoFlags = 0,
        ShowStreamButton = 1,
        ShowLegend = 2
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    explicit IVariableMeasuresUIHandler(Flags flags, CScrollableWidget *scrollable, CAutomate* arg_automate, QObject *parent = Q_NULLPTR);

protected:
    int columnCount() const Q_DECL_OVERRIDE;
    QWidget *createWidget(int index, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowInserted(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;
    void rowChanged(const Row &row, IVariable *ivar) Q_DECL_OVERRIDE;

    CAutomate* m_automate;

private:
    QWidget *newDetailsButton(IVariable *ivar);
    QWidget *newColorLegend(IVariable *ivar);
    CClickableLabel *newLabel(IVariable *ivar);
    CClickableLabel *newValueLabel(IVariable *ivar);
    CClickableLabel *newErrorLabel(IVariable *ivar);
    QString textForStreamState(CAutomate::eStateStream state) const;

private slots:
    void slotButtonMeasureDetailsClicked();
    void slotUpdateStateStream(const QString& arg_streamName, CAutomate::eStateStream state);

private:
    Flags m_flags;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(IVariableMeasuresUIHandler::Flags)

#endif // IVARIABLEMEASURESUIHANDLER_H
