#ifndef CEDITEXTENSIONWINDOW_H
#define CEDITEXTENSIONWINDOW_H

#include <QWidget>
namespace Ui {
class CEditExtensionWindow;
}
class IEditExtensionTab;

class CEditExtensionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CEditExtensionWindow(QWidget *parent = Q_NULLPTR);
    ~CEditExtensionWindow();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void backTriggered();

private:
    void addTab(IEditExtensionTab *tab, const QString &title);
    Ui::CEditExtensionWindow *ui;
};

#endif // CEDITEXTENSIONWINDOW_H
