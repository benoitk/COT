#ifndef CCONFIGURATORWINDOW_H
#define CCONFIGURATORWINDOW_H

#include <QWidget>
namespace Ui {
class CConfiguratorWindow;
}
class IConfiguratorTab;
class CConfiguratorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CConfiguratorWindow(QWidget *parent = Q_NULLPTR);
    ~CConfiguratorWindow();

private slots:
    void backTriggered();
private:
    void addTab(IConfiguratorTab *tab, const QString &title);
    Ui::CConfiguratorWindow *ui;
};

#endif // CCONFIGURATORWINDOW_H
