#ifndef CALARMSWINDOW_H
#define CALARMSWINDOW_H

#include <QWidget>
#include <QMap>
#include <QDateTime>

namespace Ui {
class CAlarmsWindow;
}

class QTextDocument;

/**
 * @brief List of pending alarms
 * This data structure stores the alarms emitted by signalUpdateAlarms,
 * so that CAlarmsWindow (when it exists) can display them.
 */
class CPendingAlarms : public QObject
{
    Q_OBJECT
public:
    CPendingAlarms(QObject *parent) : QObject(parent) {}
    // The identifier is the alarm name
    void addAlarm(const QString &id, const QDateTime &dateTime, const QString &description);
    void clearAlarms();
    bool isEmpty() const { return m_alarms.empty(); }
    QString alarmsFormattedText() const;

Q_SIGNALS:
    void changed();

private:
    struct Alarm
    {
        Alarm(const QString &id, const QDateTime &dateTime, const QString &description)
            : id(id), dateTime(dateTime), description(description) {}
        QString id;
        QDateTime dateTime;
        QString description;
    };

    std::vector<Alarm> m_alarms;
};

/**
 * @brief This window displays the current alarms.
 */
class CAutomate;
class CAlarmsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CAlarmsWindow(CAutomate* arg_automate, CPendingAlarms *alarms, QWidget *parent = Q_NULLPTR);
    ~CAlarmsWindow();

private:
    Ui::CAlarmsWindow *ui;
    CPendingAlarms *m_pendingAlarms;
    CAutomate* m_automate;

private slots:
    void backTriggered();
    void slotAlarmsChanged();
    void slotRemoveAlarms();
};

#endif // CALARMSWINDOW_H
