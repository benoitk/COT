#include "CUpdateManager.h"

#include <QFileSystemWatcher>
#include <QTimer>
#include <QFile>
#include <QSettings>

CUpdateManager::CUpdateManager(QObject *parent)
    : QObject(parent)
    , m_fileSystemWatcher(new QFileSystemWatcher(this))
    , m_timer(new QTimer(this))
    , m_process(new QProcess(this))
{
    m_timer->setInterval(5000);
    m_timer->setSingleShot(true);

    m_process->setProcessChannelMode(QProcess::MergedChannels);

    connect(m_fileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &CUpdateManager::slotDirectoryChanged);
    connect(m_timer, &QTimer::timeout, this, &CUpdateManager::slotTimeout);
    connect(m_process, static_cast<void (QProcess::*)(QProcess::ProcessError)>(&QProcess::error),
            this, &CUpdateManager::slotProcessError);
    connect(m_process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this, &CUpdateManager::slotProcessFinished);
    connect(m_process, &QProcess::readyReadStandardError, this, &CUpdateManager::slotProcessReadyReadStandardError);
    connect(m_process, &QProcess::readyReadStandardOutput, this, &CUpdateManager::slotProcessReadyReadStandardOutput);
    connect(m_process, &QProcess::started, this, &CUpdateManager::slotProcessStarted);
    connect(m_process, &QProcess::stateChanged, this, &CUpdateManager::slotProcessStateChanged);
}

CUpdateManager::~CUpdateManager()
{
}

void CUpdateManager::init()
{
    if (!m_fileSystemWatcher->addPath(COT_USB_MOUNT_POINT)) {
        qFatal("%s: Can not monitor path: %s", Q_FUNC_INFO, COT_USB_MOUNT_POINT);
    }
    else {
        m_timer->start();
    }
}

bool CUpdateManager::isRunning() const
{
    return m_process->state() == QProcess::Running;
}

void CUpdateManager::slotUpdateSoftware()
{
    if (isRunning()) {
        emit signalError(tr("The update is already in progress."));
        return;
    }

    m_process->setProgram(scriptFilePath());
    m_process->start();
}

void CUpdateManager::slotDirectoryChanged(const QString &path)
{
    if (path != COT_USB_MOUNT_POINT) {
        return;
    }

    m_timer->start();
}

void CUpdateManager::slotTimeout()
{
    const QString scriptFilePath = this->scriptFilePath();
    const QString settingsFilePath = this->settingsFilePath();

    if (!QFile::exists(settingsFilePath)) {
        qDebug("%s: Settings file do not exists.", qPrintable(settingsFilePath));
        return;
    }

    if (!QFile::exists(scriptFilePath)) {
        qDebug("%s: Script file do not exists.", qPrintable(scriptFilePath));
        return;
    }

    const QSettings settings(settingsFilePath, QSettings::IniFormat);
    const QString version = settings.value("version").toString();

    if (version.isEmpty()) {
        qDebug("%s: No version found in settings file.", qPrintable(version));
        return;
    }
    else {
        emit signalUpdateAvailable(version);
    }
}

void CUpdateManager::slotProcessError(QProcess::ProcessError error)
{
    Q_UNUSED(error);
    emit signalError(m_process->errorString());
}

void CUpdateManager::slotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        emit signalError(tr("The update process did not finished correctly: exitCode: %1, exitStatus: %2")
                         .arg(exitCode).arg(exitStatus));
    }

    emit signalFinished(exitStatus == QProcess::NormalExit && exitCode == 0);
}

void CUpdateManager::slotProcessReadyReadStandardError()
{
    emit signalReadyRead(QString::fromLocal8Bit(m_process->readAllStandardError()));
}

void CUpdateManager::slotProcessReadyReadStandardOutput()
{
    emit signalReadyRead(QString::fromLocal8Bit(m_process->readAllStandardOutput()));
}

void CUpdateManager::slotProcessStarted()
{
    //
}

void CUpdateManager::slotProcessStateChanged(QProcess::ProcessState newState)
{
    Q_UNUSED(newState);
}

QString CUpdateManager::settingsFilePath() const
{
    return QStringLiteral("%1/usb/cot-update.ini").arg(COT_USB_MOUNT_POINT);
}

QString CUpdateManager::scriptFilePath() const
{
    return QStringLiteral("%1/usb/cot-update.sh").arg(COT_USB_MOUNT_POINT);
}
