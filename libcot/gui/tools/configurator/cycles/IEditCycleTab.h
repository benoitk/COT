#ifndef IEDITCYCLETAB_H
#define IEDITCYCLETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class ICycle;

class IEditCycleTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditCycleTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

    virtual void applyProperties(ICycle *cycle) = 0;

signals:
    void signalOkTriggered();
    void signalCancelTriggered();
};

#endif // IEDITCYCLETAB_H
