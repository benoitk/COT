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
#include <QDebug>

static CPCWindow *s_mainWindow = Q_NULLPTR;

CPCWindow::CPCWindow(QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::CPCWindow)
    , m_updateManager(new CUpdateManager(this))
{
    if (!s_mainWindow)
        s_mainWindow = this;

#ifdef QT_DEBUG
    // add windows decorations when debugging
    setWindowFlags(Qt::Window);
#endif

    m_updateManager->init();

    ui->setupUi(this);
    ui->actionUpdate->setVisible(false);
    addTab(new CPCMeasureTab(this), QString());
    addTab(new CPCDiagnosticTab(this), QString());
    addTab(new CPCToolsTab(this), QString());
    addTab(new CPCHistogramTab(this), QString());
    addTab(new CPCPlusTab(this), QStringLiteral("  +  "));

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
    if (s_mainWindow == this)
        s_mainWindow = Q_NULLPTR;
    delete ui;
}

void CPCWindow::openModal(QWidget *widget) {
#if 0 //def QT_DEBUG
    // add windows decorations when debugging
    widget->setWindowFlags(Qt::Window);
#else
    widget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowModality(Qt::ApplicationModal);
    if (s_mainWindow) {
        widget->setGeometry(s_mainWindow->geometry());

        if (widget->inherits("CMessageBox")) {
            widget->adjustSize();
            QRect rect = widget->rect();
            rect.setSize(rect.size().boundedTo(s_mainWindow->size()));
            rect.moveCenter(s_mainWindow->geometry().center());
            widget->setGeometry(rect);
        }
    }
    widget->show();
}

// static
int CPCWindow::openExec(CDialog *dialog)
{
#if 0 //def QT_DEBUG
    // add windows decorations when debugging
    dialog->setWindowFlags(Qt::Dialog);
#else
    dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif
    dialog->adjustSize();
    QRect rect = QRect(QPoint(), dialog->minimumSize());
    if (s_mainWindow)
        rect.moveCenter(s_mainWindow->geometry().center());
    dialog->setGeometry(rect);
    return dialog->exec();
}

void CPCWindow::retranslate()
{
    ui->retranslateUi(this);
    ui->twPages->setTabText(0, tr("MEASURE"));
    ui->twPages->setTabText(1, tr("DIAGNOSTIC"));
    ui->twPages->setTabText(2, tr("TOOLS"));
    ui->twPages->setTabText(3, tr("GRAPHS"));
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
            ui->actionUpdate->trigger();
        }
    }
}

void CPCWindow::slotUpdateTriggered()
{
    const QString appFilePath = qApp->applicationFilePath();
    CUpdateDialog dlg(m_updateManager, this);

    if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
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
