#ifndef CPCHISTOGRAMTAB_H
#define CPCHISTOGRAMTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCHistogramTab;
}

class CPCHistogramTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCHistogramTab(QWidget *parent = Q_NULLPTR);
    ~CPCHistogramTab();

private:
    Ui::CPCHistogramTab *ui;
};

#endif // CPCHISTOGRAMTAB_H