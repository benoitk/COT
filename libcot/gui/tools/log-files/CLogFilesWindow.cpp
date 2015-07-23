#include "CLogFilesWindow.h"
#include "CVerticalButtonBar.h"
#include "CScrollablePlainTextEdit.h"
#include "CMessageBox.h"
#include "CPCWindow.h"

#include <QApplication>
#include <QAction>
#include <QTimer>
#include <QStorageInfo>
#include <QThreadPool>
#include <QProcess>
#include <QDebug>
#define QPROCESS_TIME_OUT -1 // 1000 *60 *5

CopyLogRunnable::CopyLogRunnable(const QString &source, const QString target)
    : QObject(), QRunnable()
    , m_source(source), m_target(target)
{
    setAutoDelete(true);
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
            emit signalMessage(CLogFilesWindow::tr("A problem occurs while copying the log files.\n"
                                                   "Process exited with code %1.\n\n"
                                                   "Output:\n%2")
                               .arg(process.exitCode())
                               .arg(QString::fromUtf8(process.readAllStandardOutput())));
            emit signalFinished(false);
        }
    }
}

CLogFilesWindow::CLogFilesWindow(QWidget *parent)
    : IScrollablePlainTextEdit(parent)
{
    connect(buttonBar()->addAction(CToolButton::Retry), &QAction::triggered, this, &CLogFilesWindow::slotRetryTriggered);
    buttonBar()->addAction(CToolButton::ScrollUp, scrollableWidget()->moveUp());
    buttonBar()->addAction(CToolButton::ScrollDown, scrollableWidget()->moveDown());
    connect(buttonBar()->addAction(CToolButton::Back), &QAction::triggered, this, &CLogFilesWindow::slotBackTriggered);

    QTimer::singleShot(0, this, &CLogFilesWindow::handleWork);
}

void CLogFilesWindow::closeEvent(QCloseEvent *event)
{
    if (buttonBar()->action(CToolButton::Back)->isEnabled()) {
        IScrollablePlainTextEdit::closeEvent(event);
    }
    else {
        event->ignore();
    }
}

void CLogFilesWindow::slotRetryTriggered()
{
    handleWork();
}

void CLogFilesWindow::slotBackTriggered()
{
    close();
}

void CLogFilesWindow::slotRunnableMessage(const QString &message)
{
    scrollableWidget()->setPlainText(message);
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
    qDebug() << si.isValid() << si.mountedVolumes().count() <<  si.name();
    si.refresh();
    return si.isReady() && si.isValid() && !si.isReadOnly() && (si.name()!="");
}

void CLogFilesWindow::handleWork()
{
    buttonBar()->action(CToolButton::Retry)->setVisible(false);
    scrollableWidget()->clear();

    if (isUSBKeyMounted()) {
        CMessageBox *mb = new CMessageBox(tr("Do you want to copy the log files ?"));
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
        connect(runnable, &CopyLogRunnable::signalFinished, this, &CLogFilesWindow::slotRunnableFinished);
        QThreadPool::globalInstance()->start(runnable, 1000);
    }
    else {
        scrollableWidget()->setPlainText(tr("The usb key is not mounted.\nClick the retry button to try again."));
        buttonBar()->action(CToolButton::Retry)->setVisible(true);
    }
}
