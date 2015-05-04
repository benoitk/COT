#ifndef CEDITVARIABLEWINDOW_H
#define CEDITVARIABLEWINDOW_H

#include <QWidget>
namespace Ui {
class CEditVariableWindow;
}
class IEditVariableTab;
class CEditvariableWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CEditvariableWindow(QWidget *parent = Q_NULLPTR);
    ~CEditvariableWindow();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void backTriggered();

private:
    void addTab(IEditVariableTab *tab, const QString &title);
    Ui::CEditVariableWindow *ui;
};

#endif // CEDITVARIABLEWINDOW_H
