#include "CAboutWindow.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QApplication>

// KDAB_TODO: Fix me
#define NUM_VERSION_5 "N/C"

CAboutWindow::CAboutWindow(QWidget *parent)
    : CDialog(parent)
{
    setTitle(tr("INFORMATION"));
    QLabel *lInformations = new QLabel(this);
    lInformations->setText(tr("%1 (%2)\n\nGUI version:\n%3\n%4\nSupervision version:\n%5")
                               .arg(qApp->applicationDisplayName())
                               .arg(qApp->applicationName())
                               .arg(qApp->applicationVersion())
                               .arg(analyzerString())
                               .arg(NUM_VERSION_5));
    setMainWidget(lInformations);

    connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered, this, &CAboutWindow::close);
}

CAboutWindow::~CAboutWindow()
{
}

QString CAboutWindow::analyzerString() const
{
    QString typeAnalyseur;
    typeAnalyseur = tr("COT");

    return typeAnalyseur;
}
