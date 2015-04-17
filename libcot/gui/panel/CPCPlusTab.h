#ifndef CPCPLUSTAB_H
#define CPCPLUSTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCPlusTab;
}

class CPCPlusTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCPlusTab(QWidget *parent = Q_NULLPTR);
    ~CPCPlusTab();

private:
    Ui::CPCPlusTab *ui;
};

#endif // CPCPLUSTAB_H
