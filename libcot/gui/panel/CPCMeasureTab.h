#ifndef CPCMEASURETAB_H
#define CPCMEASURETAB_H

#include "IPCTab.h"

namespace Ui {
class CPCMeasureTab;
}

class CPCMeasureTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCMeasureTab(QWidget *parent = Q_NULLPTR);
    ~CPCMeasureTab();

private slots:
    void alarmsTriggered();
    void playTriggered();
    void stopTriggered();
    void stopEndCycleTriggered();
    void nextStreamTriggered();

private:
    Ui::CPCMeasureTab *ui;
};

#endif // CPCMEASURETAB_H
