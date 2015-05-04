#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class CEditVariableTab : public QWidget
{
    Q_OBJECT
public:
    explicit CEditVariableTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // CEDITVARIABLETAB_H
