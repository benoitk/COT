#ifndef CDIALOGPASSWORD_H
#define CDIALOGPASSWORD_H

#include <QDialog>
#include <QString>
class CKeyboardNormalButton;
class QLineEdit;

#include "CDialog.h"
#include "cot_global.h"

class CKeyboardNormalButton;
class LIBCOT_EXPORT CDialogPassword :
    public CDialog
{
    Q_OBJECT
public:
    static CDialogPassword* getInstance();

    void setPassordToCheck(const QString& sPwd,const QString& sPwd2 = "");
    QString getPasswordChecked(){return m_pwdToCheck;};
public slots:
    void btZeroPressed();
    void btOnePressed();
    void btTwoPressed();
    void btThreePressed();
    void btFourPressed();
    void btFivePressed();
    void btSixPressed();
    void btSevenPressed();
    void btEightPressed();
    void btNinePressed();
    void btDeletePressed();
private:
    void setConnexion();
    CDialogPassword(QWidget* parent=Q_NULLPTR);
    void addDigit(QString sDigit);

    static CDialogPassword* singleton;
    QLineEdit *m_lblValue;
    CKeyboardNormalButton *m_btComma;
    CKeyboardNormalButton *m_btPlusMinus;
    CKeyboardNormalButton *m_btZero;
    CKeyboardNormalButton *m_btOne;
    CKeyboardNormalButton *m_btTwo;
    CKeyboardNormalButton *m_btThree;
    CKeyboardNormalButton *m_btFour;
    CKeyboardNormalButton *m_btFive;
    CKeyboardNormalButton *m_btSix;
    CKeyboardNormalButton *m_btSeven;
    CKeyboardNormalButton *m_btEight;
    CKeyboardNormalButton *m_btNine;

    QString m_pwdToCheck;
    QString m_pwdToCheck2;

};

#endif // CDIALOGPASSWORD_H
