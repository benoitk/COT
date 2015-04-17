#ifndef CPUSHBUTTON_H
#define CPUSHBUTTON_H

#include <QPushButton>

// This class represent rounded rect gray push button
class CPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit CPushButton(QWidget *parent = Q_NULLPTR);
    ~CPushButton();

protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // CPUSHBUTTON_H
