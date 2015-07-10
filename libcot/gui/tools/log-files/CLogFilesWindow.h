#ifndef CLOGFILESWINDOW_H
#define CLOGFILESWINDOW_H

#include "IScrollablePlainTextEdit.h"

#include <QRunnable>

class CopyLogRunnable : public QObject, public QRunnable
{
    Q_OBJECT

public:
    CopyLogRunnable(const QString &source, const QString target);

    void run() Q_DECL_OVERRIDE;

signals:
    void signalMessage(const QString &text);
    void signalFinished(bool success);

private:
    QString m_source;
    QString m_target;
};

class CLogFilesWindow : public IScrollablePlainTextEdit
{
    Q_OBJECT

public:
    explicit CLogFilesWindow(QWidget *parent = Q_NULLPTR);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotRetryTriggered();
    void slotBackTriggered();
    void slotRunnableMessage(const QString &message);
    void slotRunnableFinished(bool success);

private:
    QString sourceDirectory() const;
    QString targetDirectory() const;
    bool isUSBKeyMounted() const;
    void handleWork();
};

#endif // CLOGFILESWINDOW_H
