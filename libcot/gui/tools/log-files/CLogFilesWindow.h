#ifndef CLOGFILESWINDOW_H
#define CLOGFILESWINDOW_H

#include <QWidget>

namespace Ui {
class CLogFilesWindow;
}

class CLogFilesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CLogFilesWindow(QWidget *parent = Q_NULLPTR);
    ~CLogFilesWindow();

private slots:
    void backTriggered();

private:
    Ui::CLogFilesWindow *ui;
};

#endif // CLOGFILESWINDOW_H
