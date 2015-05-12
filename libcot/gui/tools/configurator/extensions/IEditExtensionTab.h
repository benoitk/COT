#ifndef IEDITEXTENSIONTAB_H
#define IEDITEXTENSIONTAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IEditExtensionTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditExtensionTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
    void okTriggered();
};

#endif // IEDITEXTENSIONTAB_H
