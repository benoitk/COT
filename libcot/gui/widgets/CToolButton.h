#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include <QToolButton>

// This class represente black squared tool button
class CToolButton : public QToolButton
{
    Q_OBJECT

public:
    enum Type {
        Invalid = -1,
        Alarms,
        Play,
        Stop,
        StopEndCycle,
        NextStream,
        ScrollUp,
        ScrollDown,
        Back,
        Update,
        On,
        Off,
        Led,
        Maintenance,
        ElectricalTests,
        Options,
        History,
        LogFiles,
        Quit
    };

    explicit CToolButton(QWidget *parent = Q_NULLPTR);
    explicit CToolButton(QAction *action, QWidget *parent = Q_NULLPTR);
    explicit CToolButton(CToolButton::Type type, QWidget *parent = Q_NULLPTR);
    explicit CToolButton(CToolButton::Type type, QAction *action, QWidget *parent = Q_NULLPTR);

    CToolButton::Type type() const;
    void setType(CToolButton::Type type);

    static QPixmap buttonPixmap(const QString& name);
    static QIcon buttonIcon(CToolButton::Type type);

protected:
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void initialize(CToolButton::Type type = CToolButton::Invalid, QAction *action = Q_NULLPTR);
    void updateVisibility();

private:
    CToolButton::Type m_type;
};

#endif // CTOOLBUTTON_H
