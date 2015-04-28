#include "CPCPlusTab.h"
#include "ui_CPCPlusTab.h"
#include "CLabelledToolButtonGrid.h"
#include "CLabelledToolButton.h"
#include "CPCWindow.h"
#include "CAboutWindow.h"

CPCPlusTab::CPCPlusTab(QWidget *parent)
    : IPCTab(parent)
    , ui(new Ui::CPCPlusTab)
    , m_buttons(new CLabelledToolButtonGrid(2, this))
{
    m_buttons->setButtons(QList<CToolButton::Type>()
                          << CToolButton::Informations
                          << CToolButton::Recovery);

    ui->setupUi(this);
    ui->swCentral->setScrollableWidget(m_buttons);
    ui->vbbButtons->addAction(CToolButton::ScrollUp, ui->swCentral->moveUp());
    ui->vbbButtons->addAction(CToolButton::ScrollDown, ui->swCentral->moveDown());

    retranslate();

    connect(m_buttons, &CLabelledToolButtonGrid::clicked, this, &CPCPlusTab::slotButtonClicked);
}

CPCPlusTab::~CPCPlusTab()
{
    delete ui;
}

void CPCPlusTab::retranslate()
{
    m_buttons->button(CToolButton::Informations)->setText(tr("Informations"));
    m_buttons->button(CToolButton::Recovery)->setText(tr("Recovery"));
}

void CPCPlusTab::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    IPCTab::changeEvent(event);
}

void CPCPlusTab::slotButtonClicked(CLabelledToolButton *button)
{
    switch (button->type()) {
        case CToolButton::Informations:
            CPCWindow::openModal<CAboutWindow>();
            break;

        case CToolButton::Recovery:
            break;

        default:
            Q_ASSERT(false);
            break;
    }
}
