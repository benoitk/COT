#ifndef CLABELLEDTOOLBUTTONGRID_H
#define CLABELLEDTOOLBUTTONGRID_H

#include "CScrollablePagerWidget.h"

#include "CToolButton.h"

class QGridLayout;
class CLabelledToolButton;

class CLabelledToolButtonGrid : public CScrollablePagerWidget
{
    Q_OBJECT

public:
    explicit CLabelledToolButtonGrid(QWidget *parent = Q_NULLPTR);
    explicit CLabelledToolButtonGrid(int layoutWidth, QWidget *parent = Q_NULLPTR);

    void setButtons(const QList<CLabelledToolButton *> buttons);
    void setButtons(const QList<CToolButton::Type> buttons);

    CLabelledToolButton *button(CToolButton::Type type) const;

private:
    QGridLayout *m_layout;
    int m_layoutWidth;
    QHash<CToolButton::Type, CLabelledToolButton *> m_buttons;

private slots:
    void slotClicked();

signals:
    void clicked(CLabelledToolButton *button);
    void typeClicked(CToolButton::Type button);
};

#endif // CLABELLEDTOOLBUTTONGRID_H
