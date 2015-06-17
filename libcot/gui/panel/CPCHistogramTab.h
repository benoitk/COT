#ifndef CPCHISTOGRAMTAB_H
#define CPCHISTOGRAMTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCHistogramTab;
}
class CVariableMeasure;
class CPlotObject;

class CPCHistogramTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCHistogramTab(QWidget *parent = Q_NULLPTR);
    ~CPCHistogramTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

private slots:
    void moveUp();
    void moveDown();
    void slotUpdatePlotting();

private:
    void updateCurves();
    void showCurve(int num);
    static QList<CVariableMeasure *> allMeasures();

    QList<CPlotObject *> m_plots;
    Ui::CPCHistogramTab *ui;
    int m_currentCurveNumber;
};

#endif // CPCHISTOGRAMTAB_H
