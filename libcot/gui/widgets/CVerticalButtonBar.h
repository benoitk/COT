#ifndef CVERTICALBUTTONBAR_H
#define CVERTICALBUTTONBAR_H

#include <QWidget>

class QAction;
class CToolButton;

class CVerticalButtonBar : public QWidget
{
    Q_OBJECT

public:
    enum Button {
        Alarms,
        Play,
        Stop,
        StopEndCycle,
        NextStream,
        ScrollUp,
        ScrollDown,
        Back,
        Update
    };

    explicit CVerticalButtonBar(QWidget *parent = Q_NULLPTR);
    ~CVerticalButtonBar();

    QAction *addAction(CVerticalButtonBar::Button button, QAction *action = Q_NULLPTR);
    QAction *action(CVerticalButtonBar::Button button) const;
    CToolButton *button(CVerticalButtonBar::Button button) const;

private:
    QHash<CVerticalButtonBar::Button, QAction *> m_actions;
    QHash<CVerticalButtonBar::Button, CToolButton *> m_buttons;
};

#endif // CVERTICALBUTTONBAR_H
