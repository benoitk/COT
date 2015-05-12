#ifndef CEDITVARIABLEWINDOW_H
#define CEDITVARIABLEWINDOW_H

#include <QWidget>
namespace Ui {
class CEditVariableWindow;
}
class IEditVariableTab;
class IVariable;
class CEditVariableTab;
class CEditOutBindsTab;
class CEditInBindsTab;

class CEditVariableWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CEditVariableWindow(IVariable *ivar, QWidget *parent = Q_NULLPTR);
    ~CEditVariableWindow();

    void setVariables(IVariable *ivar);
public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void backTriggered();
    void okTriggered();

private:
    void addTab(IEditVariableTab *tab, const QString &title);
    Ui::CEditVariableWindow *ui;
    CEditVariableTab *m_ceditVariableTab;
    CEditOutBindsTab *m_ceditOutBindsTab;
    CEditInBindsTab *m_ceditInBindsTab;
};

#endif // CEDITVARIABLEWINDOW_H
