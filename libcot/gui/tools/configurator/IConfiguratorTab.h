#ifndef ICONFIGURATORTAB_H
#define ICONFIGURATORTAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"

class IConfiguratorTab : public QWidget
{
    Q_OBJECT

public:
    explicit IConfiguratorTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

signals:
    void backTriggered();
};

#endif // ICONFIGURATORTAB_H
