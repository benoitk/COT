#ifndef CPCMEASURETAB_H
#define CPCMEASURETAB_H

#include "IPCTab.h"

namespace Ui {
class CPCMeasureTab;
}

class CToolButton;
class QLabel;
class QGridLayout;

class CPCMeasureTab : public IPCTab
{
    Q_OBJECT

    struct Row {
        Row() : button(0), label(0), valueUnit(0) { }

        CToolButton *button;
        QLabel *label;
        QLabel *valueUnit;
    };

public:
    explicit CPCMeasureTab(QWidget *parent = Q_NULLPTR);
    ~CPCMeasureTab();

private slots:
    void slotAlarmsTriggered();
    void slotPlayTriggered();
    void slotStopTriggered();
    void slotStopEndCycleTriggered();
    void slotNextStreamTriggered();
    void slotButtonMeasureDetailsClicked();
    void slotUpdateStreamsMeasures();
    void slotStreamMeasureChanged(const QString &name);

private:
    Ui::CPCMeasureTab *ui;
    QWidget *m_container;
    QGridLayout *m_containerLayout;
    QHash<QString, Row> m_rows;
};

#endif // CPCMEASURETAB_H
