#ifndef IEDITVARIABLETAB_H
#define IEDITVARIABLETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IEditVariableTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditVariableTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IEDITVARIABLETAB_H
