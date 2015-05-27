#ifndef IPCTAB
#define IPCTAB

#include <QWidget>

class CVerticalButtonBar;

class IPCTab : public QWidget
{
    Q_OBJECT

public:
    IPCTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    virtual CVerticalButtonBar *buttonBar() const = 0;
};

#endif // IPCTAB
