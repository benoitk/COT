#ifndef COPTIONSWINDOW_H
#define COPTIONSWINDOW_H

#include <QWidget>

namespace Ui {
class COptionsWindow;
}

class IOptionsTab;
class CAutomate;
class COptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit COptionsWindow(CAutomate* arg_automate, QWidget *parent = Q_NULLPTR);
    ~COptionsWindow();

private slots:
    void backTriggered();

private:
    Ui::COptionsWindow *ui;

    void addTab(QWidget *tab, const QString &title);
    CAutomate* m_automate;
};

#endif // COPTIONSWINDOW_H
