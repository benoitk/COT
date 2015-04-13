#include "CKeyboardNormalButton.h"
#include "CNumericalKeyboardWidget.h"
#include "CKeyboardSpecialButton.h"
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>

CNumericalKeyboardWidget::CNumericalKeyboardWidget(QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    initializeKeyboardLayout();
}

CNumericalKeyboardWidget::~CNumericalKeyboardWidget()
{

}

double CNumericalKeyboardWidget::number() const
{
    return m_lineEdit->text().toDouble();
}

bool CNumericalKeyboardWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::LocaleChange) {
        updateDigitalText();
        return true;
    }
    return QWidget::event(ev);
}

void CNumericalKeyboardWidget::slotButtonClicked(QChar character)
{
    m_lineEdit->setText(m_lineEdit->text().append(character));
    m_lineEdit->setFocus();
}

CKeyboardNormalButton *CNumericalKeyboardWidget::createButton(QChar character)
{
    CKeyboardNormalButton *normalButton = new CKeyboardNormalButton(this);
    normalButton->setCharacter(character);
    connect(normalButton, &CKeyboardNormalButton::clicked, this, &CNumericalKeyboardWidget::slotButtonClicked);
    return normalButton;
}

void CNumericalKeyboardWidget::initializeKeyboardLayout()
{
    QGridLayout* gridLayout = new QGridLayout;
    m_mainLayout->addLayout(gridLayout);

    gridLayout->addWidget( createButton( QLatin1Char('7') ), 0, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('8') ), 0, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('9') ), 0, 2 );
    CKeyboardSpecialButton * specialButton = new CKeyboardSpecialButton(this);
    specialButton->setText( QChar(0x2190) );
    specialButton->setSpecialKey( Qt::Key_Backspace );
    connect(specialButton, &CKeyboardSpecialButton::clicked, this, &CNumericalKeyboardWidget::slotSpecialButtonClicked);

    //TODO add backspace
    gridLayout->addWidget( specialButton, 0, 3 );

    gridLayout->addWidget( createButton( QLatin1Char('4') ), 1, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('5') ), 1, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('6') ), 1, 2 );

    specialButton = new CKeyboardSpecialButton( this );
    specialButton->setText( QChar(0x21B2) ); // "Enter" sign
    // make Enter do the same as OK
    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CNumericalKeyboardWidget::returnPressed );
    gridLayout->addWidget( specialButton, 1, 3, 2, 1 );

    gridLayout->addWidget( createButton( QLatin1Char('1') ), 2, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('2') ), 2, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('3') ), 2, 2 );
    gridLayout->addWidget( createButton( QLatin1Char('0') ), 3, 0, 1, 2  );


    m_digitalButton = new CKeyboardNormalButton(this);
    connect(m_digitalButton, &CKeyboardNormalButton::clicked, this, &CNumericalKeyboardWidget::slotDigitalButtonPressed);

    gridLayout->addWidget( m_digitalButton, 3, 2 );
    specialButton = new CKeyboardSpecialButton( this );
    specialButton->setText( QChar(0xB1) ); // "plus/minus" sign
    connect( specialButton, SIGNAL(clicked(bool)), this, SLOT(slotChangeSign(bool)) );
    gridLayout->addWidget( specialButton, 3, 3 );

    updateDigitalText();

}

void CNumericalKeyboardWidget::slotChangeSign(bool)
{
    QString number = m_lineEdit->text();
    if ( number.startsWith( QLatin1Char('-') ) )
        number = number.mid( 1 );
    else
        number.prepend( QLatin1Char('-') );
    m_lineEdit->setText( number );
}

void CNumericalKeyboardWidget::updateDigitalText()
{
    m_digitalButton->setCharacter(QLatin1Char('.'));
    //Update from local
    //TODO
}

void CNumericalKeyboardWidget::slotSpecialButtonClicked(Qt::Key key)
{
    QKeyEvent ev( QEvent::KeyPress, key, 0 /*keyState*/, QString() );
    qApp->sendEvent( m_lineEdit, &ev );
    m_lineEdit->setFocus();
}

void CNumericalKeyboardWidget::slotDigitalButtonPressed(QChar character)
{
    //TODO
}
