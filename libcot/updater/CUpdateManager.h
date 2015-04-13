#ifndef CUPDATEMANAGER_H
#define CUPDATEMANAGER_H

#include <QObject>
#include <QProcess>

#include "cot_global.h"

class QFileSystemWatcher;
class QTimer;

class COTWIDGETS_EXPORT CUpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit CUpdateManager(QObject *parent = 0);
    ~CUpdateManager();

    void init();
    bool isRunning() const;

public slots:
    void slotUpdateSoftware();

signals:
    void signalUpdateAvailable(const QString &version);
    void signalReadyRead(const QString &data);
    void signalError(const QString &error);
    void signalFinished(bool success);

private slots:
    void slotDirectoryChanged(const QString &path);
    void slotTimeout();
    void slotProcessError(QProcess::ProcessError error);
    void slotProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void slotProcessReadyReadStandardError();
    void slotProcessReadyReadStandardOutput();
    void slotProcessStarted();
    void slotProcessStateChanged(QProcess::ProcessState newState);

private:
    QFileSystemWatcher *m_fileSystemWatcher;
    QTimer *m_timer;
    QProcess *m_process;

    QString settingsFilePath() const;
    QString scriptFilePath() const;
};

#endif // CUPDATEMANAGER_H
