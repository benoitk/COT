#ifndef CEDITACTIONTAB_H
#define CEDITACTIONTAB_H

#include <CVerticalButtonBar.h>
#include <QWidget>

namespace Ui {
class CEditActionTab;
}

class CEditActionTabUIHandler;
class IAction;

// KDAB_TODO: merge with CEditActionTab?
class IEditActionTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditActionTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

    virtual void applyProperties(IAction *action) = 0;

signals:
    void signalOkTriggered();
    void signalCancelTriggered();
};


class CEditActionTab : public IEditActionTab
{
    Q_OBJECT

public:
    explicit CEditActionTab(IAction *action, QWidget *parent = Q_NULLPTR);
    ~CEditActionTab();

    void applyProperties(IAction *action) Q_DECL_OVERRIDE;

private:
    Ui::CEditActionTab *ui;
    CEditActionTabUIHandler *m_handler;
};

#endif // CEDITACTIONTAB_H
