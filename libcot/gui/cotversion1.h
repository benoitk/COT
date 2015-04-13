#ifndef COTVERSION1_H
#define COTVERSION1_H

#include <QMainWindow>
#include "../../cot_global.h"
namespace Ui {
class COTVersion1;
}

class CUpdateManager;

class COTWIDGETS_EXPORT COTVersion1 : public QMainWindow
{
    Q_OBJECT

public:
    COTVersion1(QWidget *parent = 0);
    ~COTVersion1();

private slots:
    void slotUpdateAvailable(const QString &version);
    void slotUpdateClicked();

private:
    Ui::COTVersion1 *ui;
    CUpdateManager *m_updateManager;

    bool canShowUpdatePopup() const;
};

#endif // COTVERSION1_H
