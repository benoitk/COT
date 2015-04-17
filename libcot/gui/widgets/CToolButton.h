#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include <QToolButton>

// This class represente black squared tool button
class CToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit CToolButton(QWidget *parent = Q_NULLPTR);
    explicit CToolButton(QAction *action, QWidget *parent = Q_NULLPTR);
    ~CToolButton();

private slots:
    void updateVisibility();
};

#endif // CTOOLBUTTON_H
