#ifndef IELECTRICALTESTSTAB_H
#define IELECTRICALTESTSTAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IElectricalTestsTab : public QWidget
{
    Q_OBJECT

public:
    explicit IElectricalTestsTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IELECTRICALTESTSTAB_H
