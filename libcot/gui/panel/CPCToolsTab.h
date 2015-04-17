#ifndef CPCTOOLSTAB_H
#define CPCTOOLSTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCToolsTab;
}

class CPCToolsTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCToolsTab(QWidget *parent = Q_NULLPTR);
    ~CPCToolsTab();

private:
    Ui::CPCToolsTab *ui;
};

#endif // CPCTOOLSTAB_H
