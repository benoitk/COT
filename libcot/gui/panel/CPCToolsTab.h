#ifndef CPCTOOLSTAB_H
#define CPCTOOLSTAB_H

#include "IPCTab.h"
#include "CToolButton.h"

namespace Ui {
class CPCToolsTab;
}

class CLabelledToolButton;

class CPCToolsTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCToolsTab(QWidget *parent = Q_NULLPTR);
    ~CPCToolsTab();

public slots:
    void retranslate();

protected:
    virtual void changeEvent(QEvent *event);

private:
    Ui::CPCToolsTab *ui;
    QHash<CToolButton::Type, CLabelledToolButton *> m_buttons;

private slots:
    void buttonClicked();
};

#endif // CPCTOOLSTAB_H
