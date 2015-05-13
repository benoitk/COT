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

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotRetranslate();
    void slotBackTriggered();

private:
    Ui::CConfiguratorWindow *ui;

    void addTab(IConfiguratorTab *tab);
};

#endif // CCONFIGURATORWINDOW_H
