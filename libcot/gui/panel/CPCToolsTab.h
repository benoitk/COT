#ifndef CPCTOOLSTAB_H
#define CPCTOOLSTAB_H

#include "IPCTab.h"

namespace Ui {
class CPCToolsTab;
}

class CLabelledToolButton;
class CLabelledToolButtonGrid;
class QTextDocument;

class CPCToolsTab : public IPCTab
{
    Q_OBJECT

public:
    explicit CPCToolsTab(QWidget *parent = Q_NULLPTR);
    ~CPCToolsTab();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::CPCToolsTab *ui;
    CLabelledToolButtonGrid *m_buttons;
    QTextDocument *m_history;

private slots:
    void slotButtonClicked(CLabelledToolButton *button);
    void slotInitializeHistoryDocument();
    void slotVariableChanged(const QString &name, const QDateTime &dateTime);
};

#endif // CPCTOOLSTAB_H
