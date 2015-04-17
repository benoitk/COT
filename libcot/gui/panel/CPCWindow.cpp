#include "CPCWindow.h"
#include "ui_CPCWindow.h"
#include "CPCMeasureTab.h"
#include "CPCDiagnosticTab.h"
#include "CPCToolsTab.h"
#include "CPCHistogramTab.h"
#include "CPCPlusTab.h"
#include "CMeasureWindow.h"
#include "CUpdateManager.h"
#include "CUpdateDialog.h"

CPCWindow::CPCWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CPCWindow)
    , m_updateManager(new CUpdateManager(this))
{
    m_updateManager->init();

    ui->setupUi(this);
    ui->actionUpdate->setVisible(false);
    addTab(new CPCMeasureTab(this), tr("MEASURE"));
    addTab(new CPCDiagnosticTab(this), tr("DIAGNOSTIC"));
    addTab(new CPCToolsTab(this), tr("TOOLS"));
    addTab(new CPCHistogramTab(this), tr("HISTOGRAM"));
    addTab(new CPCPlusTab(this), QStringLiteral("+"));

    CVerticalButtonBar *vbb = qobject_cast<IPCTab *>(ui->twPages->widget(0))->buttonBar();
    vbb->addAction(CVerticalButtonBar::Update, ui->actionUpdate);

    connect(m_updateManager, &CUpdateManager::signalUpdateAvailable, this, &CPCWindow::slotUpdateAvailable);
    connect(ui->actionUpdate, &QAction::triggered, this, &CPCWindow::slotUpdateTriggered);
}

CPCWindow::~CPCWindow()
{
    delete ui;
}

void CPCWindow::slotUpdateAvailable(const QString &version)
{
    ui->actionUpdate->setToolTip(tr("Upgrade to version %1").arg(version));

    if (qApp->applicationVersion() > version) {
        ui->actionUpdate->setVisible(false);
    }
    else {
        ui->actionUpdate->setVisible(true);

        if (canShowUpdatePopup()) {
            if (CUpdateDialog::requestUserUpdate(version)) {
                ui->actionUpdate->trigger();
            }
        }
    }
}

void CPCWindow::slotUpdateTriggered()
{
    const QString appFilePath = qApp->applicationFilePath();
    CUpdateDialog dlg(m_updateManager, this);

    if (dlg.exec() == QDialog::Accepted) {
        if (QProcess::startDetached(appFilePath)) {
            close();
        }
    }
}

void CPCWindow::addTab(IPCTab *tab, const QString &title)
{
    ui->twPages->addTab(tab, title);
}

bool CPCWindow::canShowUpdatePopup() const
{
    // TODO: check running cycles etc
    return !QApplication::activeModalWidget();
}
