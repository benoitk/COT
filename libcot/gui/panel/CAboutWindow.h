#ifndef CABOUTWINDOW_H
#define CABOUTWINDOW_H

#include <QDialog>

namespace Ui {
    class CAboutWindow;
}

class CAboutWindow : public QDialog
{
    Q_OBJECT
public:
    explicit CAboutWindow(QWidget *parent = Q_NULLPTR);
    ~CAboutWindow();

private:
    Ui::CAboutWindow *ui;

    QString analyzerString() const;
};

#endif // CABOUTWINDOW_H
