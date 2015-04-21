#ifndef IMAINTENANCETAB_H
#define IMAINTENANCETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IMaintenanceTab : public QWidget
{
    Q_OBJECT

public:
    IMaintenanceTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IMAINTENANCETAB_H
