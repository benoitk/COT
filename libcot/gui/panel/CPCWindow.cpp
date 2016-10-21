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
#include <CAutomate.h>
#include <CDisplayConf.h>
#include <CVariableStream.h>
#include <QDebug>

static const int s_maxMeasuresMainScreen = 1;

static CPCWindow *s_mainWindow = Q_NULLPTR;

CPCWindow::CPCWindow(CAutomate* arg_automate, QWidget *parent)
    : QWidget(parent, Qt::Window | Qt::FramelessWindowHint)
    , ui(new Ui::CPCWindow)
    , m_updateManager(new CUpdateManager(this))
    , m_automate(arg_automate)
{
    if (!s_mainWindow)
        s_mainWindow = this;

#ifdef QT_DEBUG
    // add windows decorations when debugging
    setWindowFlags(Qt::Window);
#endif

    m_updateManager->init();

    ui->setupUi(this);
    ui->actionUpdate->setVisible(true);
    addTab((m_measureTab = new CPCMeasureTab(arg_automate, this)));
    addTab((m_diagnosticTab = new CPCDiagnosticTab(arg_automate, this)));
    addTab((m_toolsTab = new CPCToolsTab(arg_automate, this)));
    addTab((m_graphTab = new CPCHistogramTab(arg_automate, this)));
    addTab((m_plusTab = new CPCPlusTab(arg_automate, this)));

    CVerticalButtonBar *vbb = qobject_cast<IPCTab *>(ui->twPages->widget(0))->buttonBar();
    vbb->addAction(CToolButton::Update, ui->actionUpdate);

    //connect(m_updateManager, &CUpdateManager::signalUpdateAvailable, this, &CPCWindow::slotUpdateAvailable);
    connect(ui->actionUpdate, &QAction::triggered, this, &CPCWindow::slotUpdateTriggered);
    connect(ui->twPages, &QTabWidget::currentChanged, m_automate, &CAutomate::slotTabChanged);
    connect(m_automate, &CAutomate::signalStreamsUpdated, this, &CPCWindow::slotStreamsUpdated);

#if !defined(DEVICE_BUILD)
    // Allow to quit the application on desktop
    QAction *quitAction = new QAction(tr("Leave COT"), this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    CToolButton *quitButton = new CToolButton(CToolButton::Quit, quitAction, this);
    quitButton->setFixedSize(QSize(18, 18));
    ui->twPages->setCornerWidget(quitButton, Qt::TopRightCorner);
#endif

    slotStreamsUpdated();
}

CPCWindow::~CPCWindow()
{
    if (s_mainWindow == this)
        s_mainWindow = Q_NULLPTR;
    delete ui;
}


void CPCWindow::openModal(QWidget *widget, bool arg_deleteOnClose) {
    if(CUserSession::getInstance()->loginUser()){ //peut être en double dans certain cas. Si des actions sont a prévoir avant l'ouverture d'une fenêtre : ex : maintenance.
#if 0 //def QT_DEBUG
        // add windows decorations when debugging
        widget->setWindowFlags(Qt::Window);
#else
        widget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
        if(arg_deleteOnClose)
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
    bool test = dialog->exec();
    return test;
}

bool CPCWindow::showGraphInMainScreen(CAutomate* arg_automate)
{
    int numMeasures = 0;
    const QList<CVariableStream*> streams = arg_automate->getListStreams();
    foreach(CVariableStream *stream, streams) {
        numMeasures += stream->getListMeasures().count();
    }
    return numMeasures <= s_maxMeasuresMainScreen;
}

void CPCWindow::retranslate()
{
    ui->retranslateUi(this);

    const int measureIndex = ui->twPages->indexOf(m_measureTab);
    const int diagnosticIndex = ui->twPages->indexOf(m_diagnosticTab);
    const int toolsIndex = ui->twPages->indexOf(m_toolsTab);
    const int graphIndex = ui->twPages->indexOf(m_graphTab);
    const int plusIndex = ui->twPages->indexOf(m_plusTab);

    ui->twPages->setTabText(measureIndex, tr("MEASURE"));
    ui->twPages->setTabText(diagnosticIndex, tr("DIAGNOSTIC"));
    ui->twPages->setTabText(toolsIndex, tr("TOOLS"));
    ui->twPages->setTabText(graphIndex, tr("GRAPHS"));
    ui->twPages->setTabText(plusIndex, QStringLiteral("  +  "));
}

void CPCWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        retranslate();
    }

    QWidget::changeEvent(event);
}

void CPCWindow::slotStreamsUpdated()
{
     if (showGraphInMainScreen(m_automate)) {
         const int index = ui->twPages->indexOf(m_graphTab);
         if(index != -1)
             ui->twPages->removeTab(index);
         m_graphTab->hide();
     }
//    if (!showGraphInMainScreen()) {
//        if (index == -1) {
//            //ui->twPages->insertTab(ui->twPages->count() -1, m_graphTab, QString());
//            m_graphTab->show();
//        }
//    }
//    else {
//        if (index != -1) {
//            ui->twPages->removeTab(index);
//            m_graphTab->hide();
//        }
//    }

    retranslate();
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
    if(CUserSession::getInstance()->loginUser()){
        const QString appFilePath = qApp->applicationFilePath() + " -platform xcb";
        CUpdateDialog dlg(m_updateManager, this);

        if (CPCWindow::openExec(&dlg) == QDialog::Accepted) {
            if (QProcess::startDetached(appFilePath)) {
                close();
            }
        }
    }
}

void CPCWindow::addTab(IPCTab *tab)
{
    ui->twPages->addTab(tab, QString());
}

bool CPCWindow::canShowUpdatePopup() const
{
    // TODO: check running cycles etc
    return !QApplication::activeModalWidget();
}
