#include "keyboardnormalbutton.h"
#include "numericalkeyboardwidget.h"
#include "keyboardspecialbutton.h"
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>

NumericalKeyboardWidget::NumericalKeyboardWidget(QWidget *parent)
    : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    initializeKeyboardLayout();
}

NumericalKeyboardWidget::~NumericalKeyboardWidget()
{

}

double NumericalKeyboardWidget::number() const
{
    return m_lineEdit->text().toDouble();
}

bool NumericalKeyboardWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::LocaleChange) {
        updateDigitalText();
        return true;
    }
    return QWidget::event(ev);
}

void NumericalKeyboardWidget::slotButtonClicked(QChar character)
{
    m_lineEdit->setText(m_lineEdit->text().append(character));
    m_lineEdit->setFocus();
}

KeyboardNormalButton *NumericalKeyboardWidget::createButton(QChar character)
{
    KeyboardNormalButton *normalButton = new KeyboardNormalButton(this);
    normalButton->setCharacter(character);
    connect(normalButton, &KeyboardNormalButton::clicked, this, &NumericalKeyboardWidget::slotButtonClicked);
    return normalButton;
}

void NumericalKeyboardWidget::initializeKeyboardLayout()
{
    QGridLayout* gridLayout = new QGridLayout;
    m_mainLayout->addLayout(gridLayout);

    gridLayout->addWidget( createButton( QLatin1Char('7') ), 0, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('8') ), 0, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('9') ), 0, 2 );
    KeyboardSpecialButton * specialButton = new KeyboardSpecialButton(this);
    specialButton->setText( QChar(0x2190) );
    specialButton->setSpecialKey( Qt::Key_Backspace );
    connect(specialButton, &KeyboardSpecialButton::clicked, this, &NumericalKeyboardWidget::slotSpecialButtonClicked);

    //TODO add backspace
    gridLayout->addWidget( specialButton, 0, 3 );

    gridLayout->addWidget( createButton( QLatin1Char('4') ), 1, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('5') ), 1, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('6') ), 1, 2 );

    specialButton = new KeyboardSpecialButton( this );
    specialButton->setText( QChar(0x21B2) ); // "Enter" sign
    // make Enter do the same as OK
    connect( specialButton, &KeyboardSpecialButton::clicked, this, &NumericalKeyboardWidget::returnPressed );
    gridLayout->addWidget( specialButton, 1, 3, 2, 1 );

    gridLayout->addWidget( createButton( QLatin1Char('1') ), 2, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('2') ), 2, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('3') ), 2, 2 );
    gridLayout->addWidget( createButton( QLatin1Char('0') ), 3, 0, 1, 2  );


    m_digitalButton = new KeyboardNormalButton(this);
    connect(m_digitalButton, &KeyboardNormalButton::clicked, this, &NumericalKeyboardWidget::slotDigitalButtonPressed);

    gridLayout->addWidget( m_digitalButton, 3, 2 );
    specialButton = new KeyboardSpecialButton( this );
    specialButton->setText( QChar(0xB1) ); // "plus/minus" sign
    connect( specialButton, SIGNAL(clicked(bool)), this, SLOT(slotChangeSign(bool)) );
    gridLayout->addWidget( specialButton, 3, 3 );

    updateDigitalText();

}

void NumericalKeyboardWidget::slotChangeSign(bool)
{
    QString number = m_lineEdit->text();
    if ( number.startsWith( QLatin1Char('-') ) )
        number = number.mid( 1 );
    else
        number.prepend( QLatin1Char('-') );
    m_lineEdit->setText( number );
}

void NumericalKeyboardWidget::updateDigitalText()
{
    m_digitalButton->setCharacter(QLatin1Char('.'));
    //Update from local
    //TODO
}

void NumericalKeyboardWidget::slotSpecialButtonClicked(Qt::Key key)
{
    QKeyEvent ev( QEvent::KeyPress, key, 0 /*keyState*/, QString() );
    qApp->sendEvent( m_lineEdit, &ev );
    m_lineEdit->setFocus();
}

void NumericalKeyboardWidget::slotDigitalButtonPressed(QChar character)
{
    //TODO
}
