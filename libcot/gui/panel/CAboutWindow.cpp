#include "CAboutWindow.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QApplication>



CAboutWindow::CAboutWindow(QWidget *parent)
    : CDialog(parent)
{
    setTitle(tr("INFORMATION"));
    QLabel *lInformations = new QLabel(this);
    lInformations->setText(tr("%1 Soft version:\n%2")
                               .arg(qApp->applicationName())
                               .arg(qApp->applicationVersion()));
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
