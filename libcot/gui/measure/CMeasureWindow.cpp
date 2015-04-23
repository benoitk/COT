#include "CMeasureWindow.h"
#include "ui_CMeasureWindow.h"
#include "CMeasureStreamTab.h"
#include "CMeasureMeasureTab.h"
#include "CAutomate.h"

CMeasureWindow::CMeasureWindow(const QString &stream, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CMeasureWindow)
{
    ui->setupUi(this);

    // KDAB: Fix me when customer api ready
    const QString theStream = stream.isEmpty() ? "stream_1" : stream;
    CAutomate *automate = CAutomate::getInstance();
    const QStringList variables = automate->getStreamVariables(theStream);
    const QMap<QString, QStringList> measures = automate->getStreamMeasures(theStream);

    addTab(new CMeasureStreamTab(variables, this), theStream.toUpper());

    foreach (const QString &measure, measures.keys()) {
        addTab(new CMeasureMeasureTab(measures.value(measure), this), measure.toUpper());
    }
}

CMeasureWindow::~CMeasureWindow()
{

}

void CMeasureWindow::backTriggered()
{
    close();
}

void CMeasureWindow::addTab(IMeasureTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IMeasureTab::backTriggered, this, &CMeasureWindow::backTriggered);
}
