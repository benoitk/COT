#ifndef CLOGFILESWINDOW_H
#define CLOGFILESWINDOW_H

#include "CDialog.h"

#include <QRunnable>

class QLabel;

class CopyLogRunnable : public QObject, public QRunnable
{
    Q_OBJECT

public:
    CopyLogRunnable(const QString &source, const QString &target);

    void run() Q_DECL_OVERRIDE;

signals:
    void signalMessage(const QString &text);
    void signalError(const QString &text);
    void signalFinished(bool success);

private:
    QString m_source;
    QString m_target;
};

class CLogFilesWindow : public CDialog
{
    Q_OBJECT

public:
    explicit CLogFilesWindow(QWidget *parent = Q_NULLPTR);

public slots:
    void done(int result) Q_DECL_OVERRIDE;

private slots:
    void slotCenterInParent();
    void slotRetryTriggered();
    void slotBackTriggered();
    void slotRunnableMessage(const QString &text);
    void slotRunnableError(const QString &text);
    void slotRunnableFinished(bool success);

private:
    QLabel* m_label;

    QString sourceDirectory() const;
    QString targetDirectory() const;
    bool isUSBKeyMounted() const;
    void handleWork();
};

#endif // CLOGFILESWINDOW_H
