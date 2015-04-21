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
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::CPCWindow)
    , m_updateManager(new CUpdateManager(this))
{
    m_updateManager->init();

    ui->setupUi(this);
    ui->actionUpdate->setVisible(false);
    addTab(new CPCMeasureTab(this), QString());
    addTab(new CPCDiagnosticTab(this), QString());
    addTab(new CPCToolsTab(this), QString());
    addTab(new CPCHistogramTab(this), QString());
    addTab(new CPCPlusTab(this), QStringLiteral("+"));

    CVerticalButtonBar *vbb = qobject_cast<IPCTab *>(ui->twPages->widget(0))->buttonBar();
    vbb->addAction(CToolButton::Update, ui->actionUpdate);

    connect(m_updateManager, &CUpdateManager::signalUpdateAvailable, this, &CPCWindow::slotUpdateAvailable);
    connect(ui->actionUpdate, &QAction::triggered, this, &CPCWindow::slotUpdateTriggered);

#if !defined(DEVICE_BUILD)
    // Allow to quit the application on desktop
    QAction *quitAction = new QAction(tr("Leave COT"), this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    CToolButton *quitButton = new CToolButton(CToolButton::Quit, quitAction, this);
    quitButton->setFixedSize(QSize(18, 18));
    ui->twPages->setCornerWidget(quitButton, Qt::TopRightCorner);
#endif

    retranslate();
}

CPCWindow::~CPCWindow()
{
    delete ui;
}

void CPCWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("MEASURE"));
    ui->twPages->setTabText(1, tr("DIAGNOSTIC"));
    ui->twPages->setTabText(2, tr("TOOLS"));
    ui->twPages->setTabText(3, tr("HISTOGRAM"));
}

void CPCWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
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
