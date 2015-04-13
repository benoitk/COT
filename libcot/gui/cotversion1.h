#ifndef COTVERSION1_H
#define COTVERSION1_H

#include <QMainWindow>

namespace Ui {
class COTVersion1;
}

class COTVersion1 : public QMainWindow
{
    Q_OBJECT

public:
    COTVersion1(QWidget *parent = 0);
    ~COTVersion1();

private:
    Ui::COTVersion1 *ui;
};

#endif // COTVERSION1_H
