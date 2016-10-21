#ifndef IPCTAB
#define IPCTAB

#include <QWidget>

class CVerticalButtonBar;
class CAutomate;
class IPCTab : public QWidget
{
    Q_OBJECT

public:
    IPCTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR) : QWidget(parent), m_automate(arg_automate) { }

    virtual CVerticalButtonBar *buttonBar() const = 0;

protected:
    CAutomate* m_automate;

};

#endif // IPCTAB
