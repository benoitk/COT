#ifndef CPCPLUSTAB_H
#define CPCPLUSTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCPlusTab;
}

class CLabelledToolButton;
class CLabelledToolButtonGrid;

class CPCPlusTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCPlusTab(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~CPCPlusTab();

    CVerticalButtonBar *buttonBar() const Q_DECL_OVERRIDE;

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::CPCPlusTab *ui;
    CLabelledToolButtonGrid *m_buttons;

private slots:
    void slotButtonClicked(CLabelledToolButton *button);
};

#endif // CPCPLUSTAB_H
