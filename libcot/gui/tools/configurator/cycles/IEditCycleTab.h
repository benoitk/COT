#ifndef IEDITCYCLETAB_H
#define IEDITCYCLETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IEditCycleTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditCycleTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IEDITCYCLETAB_H
