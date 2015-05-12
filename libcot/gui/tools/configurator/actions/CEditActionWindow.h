#ifndef CEDITACTIONWINDOW_H
#define CEDITACTIONWINDOW_H

#include <QWidget>

namespace Ui {
class CEditActionWindow;
}

class IEditActionTab;
class CEditActionTab;
class CEditActionStepsTab;
class IAction;

class CEditActionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CEditActionWindow(IAction *action, QWidget *parent = Q_NULLPTR);
    ~CEditActionWindow();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotOkTriggered();
    void slotCancelTriggered();

private:
    IAction *m_action;
    Ui::CEditActionWindow *ui;
    CEditActionTab *m_ceditActionTab;
    CEditActionStepsTab *m_ceditActionStepsTab;

    void addTab(IEditActionTab *tab, const QString &title);
};

#endif // CEDITACTIONWINDOW_H
