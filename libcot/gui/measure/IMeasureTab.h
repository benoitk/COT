#ifndef IMEASURETAB_H
#define IMEASURETAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IMeasureTab : public QWidget
{
    Q_OBJECT

public:
    IMeasureTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // IMEASURETAB_H
