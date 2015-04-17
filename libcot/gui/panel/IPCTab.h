#ifndef IPCTAB
#define IPCTAB

#include <QWidget>

#include "CVerticalButtonBar.h"

class IPCTab : public QWidget
{
    Q_OBJECT

public:
    IPCTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }
};

#endif // IPCTAB
