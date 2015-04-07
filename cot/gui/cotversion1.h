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

private slots:
    void slotExportTranslations();
    void slotImportTranslations();

private:
    Ui::COTVersion1 *ui;

    QString jsonFilePath() const;
    QString translationsPath() const;
};

#endif // COTVERSION1_H
