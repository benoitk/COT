#include "CDialogPassword.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "CKeyboardNormalButton.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"
#include "QAction"

CDialogPassword* CDialogPassword::singleton = 0;
CDialogPassword::CDialogPassword(QWidget*  parent): CDialog(parent)
{

   // connect(m_buttonBar->addAction(CToolButton::Ok), &QAction::triggered, this, &CDialogPassword::accept);
    connect(m_buttonBar->addAction(CToolButton::Delete), &QAction::triggered, this, &CDialogPassword::btDeletePressed);
    connect(m_buttonBar->addAction(CToolButton::Back), &QAction::triggered, this, &CDialogPassword::reject);


    QWidget* widgetMain= new QWidget(this);

    //Block du milleu
    m_lblValue = new QLineEdit(tr(""), this);
    m_lblValue->setEchoMode(QLineEdit::Password);
    m_lblValue->setEnabled(false);
    m_lblValue->setObjectName("lineEditPwd");
    //: Virgule à changer en point pour les nombres
    m_btComma = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btComma->setCharacter(',');
    m_btPlusMinus = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btPlusMinus->setCharacter('-');
    m_btZero = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btZero->setCharacter('0');
    m_btOne = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btOne->setCharacter('1');
    m_btTwo = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btTwo->setCharacter('2');
    m_btThree = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btThree->setCharacter('3');
    m_btFour = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btFour->setCharacter('4');
    m_btFive = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btFive->setCharacter('5');
    m_btSix = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btSix->setCharacter('6');
    m_btSeven = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btSeven->setCharacter('7');
    m_btEight = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btEight->setCharacter('8');
    m_btNine = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    m_btNine->setCharacter('9');

    QGridLayout* gridLayoutPaveNum = new QGridLayout();
    gridLayoutPaveNum->addWidget(m_btOne, 0, 0, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btTwo, 0, 1, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btThree, 0, 2, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btFour, 1, 0, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btFive, 1, 1, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btSix, 1, 2, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btSeven, 2, 0, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btEight, 2, 1, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btNine, 2, 2, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btPlusMinus, 3, 0, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btZero, 3, 1, Qt::AlignCenter);
    gridLayoutPaveNum->addWidget(m_btComma, 3, 2, Qt::AlignCenter);

    QVBoxLayout* vLayoutPaveNum = new QVBoxLayout();
    vLayoutPaveNum->addWidget(m_lblValue, 0, Qt::AlignRight);
    vLayoutPaveNum->addLayout(gridLayoutPaveNum);




    //Assemblage des trois principaux layout
    QHBoxLayout* hLayout = new QHBoxLayout(); //parent: widgetMain
    hLayout->addLayout(vLayoutPaveNum);
    widgetMain->setLayout(hLayout);
    //: Nom de l'onglet à mettre en majuscule dans toutes les langues si possible
    setTitle(tr("AUTHENTICATION"));
    setMainWidget(widgetMain);

    setConnexion();
}
void CDialogPassword::setPassordToCheck(const QString& sPwd,const QString& sPwd2)
{
    m_pwdToCheck = sPwd;
    m_pwdToCheck2 = sPwd2;
    m_lblValue->clear();
}

//SLOT
void CDialogPassword::btDeletePressed()
{
    m_lblValue->setText("");

}
//SLOT
void CDialogPassword::btZeroPressed()
{
    addDigit("0");
}
//SLOT
void CDialogPassword::btOnePressed()
{
    addDigit("1");
}
//SLOT
void CDialogPassword::btTwoPressed()
{
    addDigit("2");
}
//SLOT
void CDialogPassword::btThreePressed()
{
    addDigit("3");
}
//SLOT
void CDialogPassword::btFourPressed()
{
    addDigit("4");
}
//SLOT
void CDialogPassword::btFivePressed()
{
    addDigit("5");
}
//SLOT
void CDialogPassword::btSixPressed()
{
    addDigit("6");
}
//SLOT
void CDialogPassword::btSevenPressed()
{
    addDigit("7");
}
//SLOT
void CDialogPassword::btEightPressed()
{
    addDigit("8");
}
//SLOT
void CDialogPassword::btNinePressed()
{
    addDigit("9");
}
void CDialogPassword::addDigit(QString sDigit)
{
    QString sTemp = m_lblValue->text();
    sTemp.append(sDigit);
    m_lblValue->setText(sTemp);
    if(m_lblValue->text().count() == 4)
    {
        if(m_lblValue->text() == m_pwdToCheck || m_lblValue->text() == m_pwdToCheck2)
        {
            m_lblValue->setText(sTemp);
            m_pwdToCheck = sTemp;
            this->accept();
        }
        else
            m_lblValue->clear();

    }


}
void CDialogPassword::setConnexion()
{

    connect(m_btOne, SIGNAL(clicked()), this, SLOT(btOnePressed()));
    connect(m_btTwo, SIGNAL(clicked()), this, SLOT(btTwoPressed()));
    connect(m_btThree, SIGNAL(clicked()), this, SLOT(btThreePressed()));
    connect(m_btFour, SIGNAL(clicked()), this, SLOT(btFourPressed()));
    connect(m_btFive, SIGNAL(clicked()), this, SLOT(btFivePressed()));
    connect(m_btSix, SIGNAL(clicked()), this, SLOT(btSixPressed()));
    connect(m_btSeven, SIGNAL(clicked()), this, SLOT(btSevenPressed()));
    connect(m_btEight, SIGNAL(clicked()), this, SLOT(btEightPressed()));
    connect(m_btNine, SIGNAL(clicked()), this, SLOT(btNinePressed()));
    connect(m_btZero, SIGNAL(clicked()), this, SLOT(btZeroPressed()));

    //RAZ des valeurs lors de la fermeture
    connect(this, SIGNAL(accepted()), m_lblValue, SLOT(clear()));
    connect(this, &CDialogPassword::rejected, m_lblValue, &QLineEdit::clear);
}

CDialogPassword* CDialogPassword::getInstance()
{
    if(!singleton)
            singleton = new CDialogPassword();
    disconnect(singleton, 0,0,0);
    return singleton;
}
