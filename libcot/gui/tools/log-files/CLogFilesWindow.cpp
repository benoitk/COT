#include "CLogFilesWindow.h"
#include "CVerticalButtonBar.h"
#include "CScrollablePlainTextEdit.h"
#include "CMessageBox.h"
#include "CPCWindow.h"

#include <QLabel>
#include <QApplication>
#include <QAction>
#include <QTimer>
#include <QStorageInfo>
#include <QThreadPool>
#include <QProcess>
#include "qdebug.h"
#define QPROCESS_TIME_OUT -1 // 1000 *60 *5

CopyLogRunnable::CopyLogRunnable(const QString &source, const QString &target)
    : QObject(), QRunnable()
    , m_source(source), m_target(target)
{
    setAutoDelete(true);
    //setAutoDelete(false);
}

void CopyLogRunnable::run()
{
    emit signalMessage(CLogFilesWindow::tr("Copy in progress... please wait..."));

    qDebug("Copying log files from '%s' to '%s'", qPrintable(m_source), qPrintable(m_target));

    // Create path if needed for debugging outside usb devices
    {
        QDir dir;

        if (!dir.mkpath(m_target)) {
            emit signalMessage(CLogFilesWindow::tr("Can't create target: %1").arg(m_target));
            emit signalFinished(false);
            return;
        }

        dir.setPath(m_source);

        if (dir.entryList(QDir::AllEntries).isEmpty()) {
            emit signalMessage(CLogFilesWindow::tr("Nothing to copy, the source folder is empty."));
            emit signalFinished(false);
            return;
        }
    }

    // Delete existing target
    /*{
        const QString directoryName = QFileInfo(m_source).fileName();
        const QString targetToDelete = QString("%1/%2").arg(m_target).arg(directoryName);

        if (QDir(targetToDelete).exists()) {
            QProcess process;
            const QString command = "rm";
            const QStringList parameters = QStringList()
                    << "-fr"
                    << targetToDelete;

            process.setProcessChannelMode(QProcess::MergedChannels);
            process.start(command, parameters);

            if (!process.waitForStarted()) {
                emit signalMessage(CLogFilesWindow::tr("Can't start the command %1 %2")
                                   .arg(command)
                                   .arg(parameters.join(" ")));
                emit signalFinished(false);
                return;
            }

            if (!process.waitForFinished(QPROCESS_TIME_OUT)) {
                emit signalMessage(CLogFilesWindow::tr("Can't finished the command %1 %2")
                                   .arg(command)
                                   .arg(parameters.join(" ")));
                emit signalFinished(false);
                return;
            }

            if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
                emit signalMessage(CLogFilesWindow::tr("Can't delete existing target: %1.\n"
                                                       "Process exited with code %2.\n\n"
                                                       "Output:\n%3")
                                   .arg(targetToDelete)
                                   .arg(process.exitCode())
                                   .arg(QString::fromUtf8(process.readAllStandardOutput())));
                emit signalFinished(false);
                return;
            }
        }
    }*/

    // Copy files recursively
    {
        QProcess process;
        const QString command = "cp";
        const QStringList parameters = QStringList()
                << "-fr"
                << m_source
                << m_target;

        process.setProcessChannelMode(QProcess::MergedChannels);
        process.start(command, parameters);

        if (!process.waitForStarted()) {
            emit signalMessage(CLogFilesWindow::tr("Can't start the command %1 %2")
                               .arg(command)
                               .arg(parameters.join(" ")));
            emit signalFinished(false);
            return;
        }

        if (!process.waitForFinished(QPROCESS_TIME_OUT)) {
            emit signalMessage(CLogFilesWindow::tr("Can't finished the command %1 %2")
                               .arg(command)
                               .arg(parameters.join(" ")));
            emit signalFinished(false);
            return;
        }

        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            process.start("sync");
            process.waitForFinished(QPROCESS_TIME_OUT);
            emit signalMessage(CLogFilesWindow::tr("The copy of the log files was done succesfuly."));
            emit signalFinished(true);
        }
        else {
            const QString error = QString::fromLocal8Bit(process.readAllStandardOutput());
            emit signalMessage(CLogFilesWindow::tr("A problem occurs while copying the log files.\n"
                                                   "Process exited with code %1.")
                               .arg(process.exitCode()));
            emit signalError(error);
            emit signalFinished(false);

            qDebug("%s: Copy fails: \n%s", Q_FUNC_INFO, qPrintable(error));
        }
    }
}

CLogFilesWindow::CLogFilesWindow(QWidget *parent)
    : CDialog(parent)
    , m_label(new QLabel(this))
{
    qDebug() << "CLogFilesWindow::CLogFilesWindow(QWidget *parent)";
    setTitle(tr("Copying log files"));
    setMainWidget(m_label);

    connect(buttonBar()->addAction(CToolButton::Retry), &QAction::triggered, this, &CLogFilesWindow::slotRetryTriggered);
    connect(buttonBar()->addAction(CToolButton::Back), &QAction::triggered, this, &CLogFilesWindow::slotBackTriggered);

    QTimer::singleShot(0, this, &CLogFilesWindow::handleWork);
    qDebug() << "FIN CLogFilesWindow::CLogFilesWindow(QWidget *parent)";
}

void CLogFilesWindow::done(int result)
{
    if (buttonBar()->action(CToolButton::Back)->isEnabled()) {
        CDialog::done(result);
    }
}

void CLogFilesWindow::slotCenterInParent()
{
    qDebug() << "CLogFilesWindow::slotCenterInParent()";
    // Need to center again due to label size changing width
    qDebug() << "parent" << parentWidget();
    if(parentWidget()){
    const QRect prect = parentWidget()->geometry();
    QRect rect = geometry();
    rect.moveCenter(prect.center());
    setGeometry(rect);
    }
    else
        qDebug() << "Pas de parent";
    qDebug() << "FIN CLogFilesWindow::slotCenterInParent()";
}

void CLogFilesWindow::slotRetryTriggered()
{
    handleWork();
}

void CLogFilesWindow::slotBackTriggered()
{
    close();
}

void CLogFilesWindow::slotRunnableMessage(const QString &text)
{
    qDebug() << "CLogFilesWindow::slotRunnableMessage";
    m_label->setText(text);
    QTimer::singleShot(25, this, &CLogFilesWindow::slotCenterInParent);
    qDebug() << "FIN CLogFilesWindow::slotRunnableMessage";
}

void CLogFilesWindow::slotRunnableError(const QString &text)
{
    if (text.contains(QStringLiteral("No space left on device"))) {
        m_label->setText(tr("There is not enough space to copy log files on the USB key."));
    }
    else if (text.contains(QStringLiteral("Permission denied"))) {
        m_label->setText(tr("You do not have permission to write on the USB key."));
    }
    else if (text.contains(QStringLiteral("Read-only file system"))) {
        m_label->setText(tr("You do not have permission to write on the USB key because the file system is read only."));
    }
    else {
        m_label->setText(tr("An unknown error appeared while copying log files on the USB key."));
    }

    QTimer::singleShot(25, this, &CLogFilesWindow::slotCenterInParent);
}

void CLogFilesWindow::slotRunnableFinished(bool success)
{
    buttonBar()->action(CToolButton::Retry)->setVisible(success ? false : true);
    buttonBar()->action(CToolButton::Back)->setEnabled(true);
}

QString CLogFilesWindow::sourceDirectory() const
{
    QString source = QString::fromUtf8(LOG_SOURCE_DIRECTORY);

    if (source.endsWith("/") && source != "/") {
        source.chop(1);
    }

    return source;
}

QString CLogFilesWindow::targetDirectory() const
{
    QString target = QString::fromUtf8("%1/USB").arg(QString::fromUtf8(COT_USB_MOUNT_POINT));

    if (target.endsWith("/") && target != "/") {
        target.chop(1);
    }

    return target;
}

bool CLogFilesWindow::isUSBKeyMounted() const
{
    QStorageInfo si(targetDirectory());
    si.refresh();
    return si.isReady() && si.isValid() && !si.name().isEmpty();
}

void CLogFilesWindow::handleWork()
{
    qDebug() << "CLogFilesWindow::handleWork()";
    buttonBar()->action(CToolButton::Retry)->setVisible(false);
    m_label->clear();

    if (isUSBKeyMounted()) {
        qDebug() << "clé monté";
        CMessageBox *mb = new CMessageBox(tr("Do you want to copy the log files ?"));
        mb->setAttribute(Qt::WA_DeleteOnClose);
        mb->setTitle(tr("CONFIRMATION!"));
        QAction *cancelAction = mb->buttonBar()->addAction(CToolButton::Cancel);
        connect(cancelAction, &QAction::triggered, mb, &QDialog::reject);
        if (CPCWindow::openExec(mb) != QDialog::Accepted) {
            close();
            return;
        }

        buttonBar()->action(CToolButton::Back)->setEnabled(false);
        CopyLogRunnable *runnable = new CopyLogRunnable(sourceDirectory(), targetDirectory());
        connect(runnable, &CopyLogRunnable::signalMessage, this, &CLogFilesWindow::slotRunnableMessage);
        connect(runnable, &CopyLogRunnable::signalError, this, &CLogFilesWindow::slotRunnableError);
        connect(runnable, &CopyLogRunnable::signalFinished, this, &CLogFilesWindow::slotRunnableFinished);
        if(!QThreadPool::globalInstance()->tryStart(runnable)){
            QThreadPool::globalInstance()->setMaxThreadCount(QThreadPool::globalInstance()->maxThreadCount()+1);
            if(!QThreadPool::globalInstance()->tryStart(runnable)){
                qDebug() << "QThreadPool::globalInstance()->start fail";
            }
        }
    }
    else {
        qDebug() << "clé non monté";
        slotRunnableMessage(tr("The usb key is not mounted.\nClick the retry button to try again."));
        buttonBar()->action(CToolButton::Retry)->setVisible(true);
    }
    qDebug() << "FIN CLogFilesWindow::handleWork()";
}
