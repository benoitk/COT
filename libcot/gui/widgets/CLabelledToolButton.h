#ifndef CLABELLEDTOOLBUTTON_H
#define CLABELLEDTOOLBUTTON_H

#include "CToolButton.h"

class QLabel;

class CLabelledToolButton : public QWidget
{
    Q_OBJECT

public:
    explicit CLabelledToolButton(CToolButton::Type type, QWidget *parent = Q_NULLPTR);
    explicit CLabelledToolButton(CToolButton::Type type, QAction *action, QWidget *parent = Q_NULLPTR);

    CToolButton::Type type() const;
    void setType(CToolButton::Type type);

    QString text() const;

public slots:
    void setText(const QString &text);

protected:
    CToolButton *button() const;
    QLabel *label() const;

private:
    CToolButton *m_toolButton;
    QLabel *m_label;

    void initialize();

signals:
    void clicked();
};

#endif // CLABELLEDTOOLBUTTON_H
