#ifndef LOCALCOMBOBOX_H
#define LOCALCOMBOBOX_H

#include <QComboBox>
#include <QLocale>
class LocalComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LocalComboBox(QWidget *parent = Q_NULLPTR);
    ~LocalComboBox();

Q_SIGNALS:
    void localeSelected(QLocale::Language);
private slots:
    void slotLocalActivated(int);
private:
    void initializeLocale();
};
Q_DECLARE_METATYPE(QLocale::Language)
#endif // LOCALCOMBOBOX_H
