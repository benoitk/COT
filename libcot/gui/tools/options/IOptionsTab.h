#ifndef IOPTIONSTAB_H
#define IOPTIONSTAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IOptionsTab : public QWidget
{
    Q_OBJECT

public:
    IOptionsTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IOPTIONSTAB_H
