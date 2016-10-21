#ifndef CPCHISTOGRAMTAB_H
#define CPCHISTOGRAMTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCHistogramTab;
}
class CVariableMeasure;
class CPlotObject;
class IVariableMeasuresUIHandler;

class CPCHistogramTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCHistogramTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CPCHistogramTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

private slots:
    void moveUp();
    void moveDown();
    void slotUpdatePlotting();

private:
    void updateCurves();
    void updateActions();
    void showCurve(int num);

    QList<CPlotObject *> m_plots;
    Ui::CPCHistogramTab *ui;
    int m_currentCurveNumber;
    IVariableMeasuresUIHandler *m_measuresHandler;
};

#endif // CPCHISTOGRAMTAB_H
