#include "CEditExtensionWindow.h"
#include "ui_CEditExtensionWindow.h"
#include "IEditExtensionTab.h"
#include "CEditGeneralTab.h"
#include "CEditComTab.h"
#include "CEditOrgansTab.h"

#include <IVariable.h>

CEditExtensionWindow::CEditExtensionWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CEditExtensionWindow)
{
    ui->setupUi(this);

    addTab(new CEditGeneralTab(), QString());
    addTab(new CEditComTab(), QString());
    addTab(new CEditGeneralTab(), QString());
    retranslate();
}

CEditExtensionWindow::~CEditExtensionWindow()
{
    delete ui;
}

void CEditExtensionWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("General"));
    ui->twPages->setTabText(1, tr("Com"));
    ui->twPages->setTabText(2, tr("Organs"));
}

void CEditExtensionWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}


void CEditExtensionWindow::backTriggered()
{
    close();
}

void CEditExtensionWindow::addTab(IEditExtensionTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
    connect(tab, &IEditExtensionTab::backTriggered, this, &CEditExtensionWindow::backTriggered);
}
