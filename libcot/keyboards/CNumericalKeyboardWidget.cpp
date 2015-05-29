#include "CKeyboardNormalButton.h"
#include "CNumericalKeyboardWidget.h"
#include "CKeyboardSpecialButton.h"

#include <IVariable.h>

#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QDoubleValidator>

#include <limits>

namespace {
// We deal only with float so limits values.
const float MIN_VALUE = 0.0;
const float MAX_VALUE = std::numeric_limits<float>::max();

QDoubleValidator *newValidator(QObject *parent = Q_NULLPTR) {
    return new QDoubleValidator(MIN_VALUE, MAX_VALUE, IVariable::FLOAT_PRECISION, parent);
}
}

CNumericalKeyboardWidget::CNumericalKeyboardWidget(QWidget *parent)
    : QWidget(parent)
    , m_mode(CNumericalKeyboardWidget::Double)
{
    m_mainLayout = new QVBoxLayout(this);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setValidator(newValidator(m_lineEdit));
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    initializeKeyboardLayout();
}

CNumericalKeyboardWidget::CNumericalKeyboardWidget(CNumericalKeyboardWidget::Mode mode, QWidget *parent)
    : QWidget(parent)
    , m_mode(mode)
{
    m_mainLayout = new QVBoxLayout(this);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setValidator(newValidator(m_lineEdit));
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    initializeKeyboardLayout();
}

CNumericalKeyboardWidget::~CNumericalKeyboardWidget()
{

}

CNumericalKeyboardWidget::Mode CNumericalKeyboardWidget::mode() const
{
    return m_mode;
}

void CNumericalKeyboardWidget::setMode(const CNumericalKeyboardWidget::Mode &mode)
{
    if (m_mode != mode) {
        m_mode = mode;
        m_digitalButton->setVisible(m_mode == CNumericalKeyboardWidget::Double);
    }
}

int CNumericalKeyboardWidget::integerNumber() const
{
    const QString text = m_lineEdit->text();
    const int value = lineEditLocale().toInt(text);
    return value;
}

void CNumericalKeyboardWidget::setIntegerNumber(int number)
{
    m_lineEdit->setText(lineEditLocale().toString(number));
}

double CNumericalKeyboardWidget::doubleNumber() const
{
    const QString text = m_lineEdit->text();
    const double value = lineEditLocale().toDouble(text);
    return value;
}

void CNumericalKeyboardWidget::setDoubleNumber(double number)
{
    m_lineEdit->setText(lineEditLocale().toString(number, 'f', IVariable::FLOAT_PRECISION));
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
    const QChar decimalSeparator = lineEditLocale().decimalPoint();
    QString text = m_lineEdit->text();
    const double value = lineEditLocale().toDouble(text);

    if ((character == decimalSeparator) || text.startsWith(QStringLiteral("-"))) {
        text.append(character);
    } else if (text.contains(decimalSeparator)) {
        text.append(character);
    } else if (qFuzzyCompare(value + 1.0, 1.0) ) {
        text = character;
    } else {
        text.append(character);
    }

    setFixedText(text);
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
    specialButton->setAutoRepeat(true);
    connect(specialButton, &CKeyboardSpecialButton::clicked, this, &CNumericalKeyboardWidget::slotBlackspaceButtonClicked);

    gridLayout->addWidget( specialButton, 0, 3 );

    gridLayout->addWidget( createButton( QLatin1Char('4') ), 1, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('5') ), 1, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('6') ), 1, 2 );

#if 0
    specialButton = new CKeyboardSpecialButton( this );
    specialButton->setText( QChar(0x21B2) ); // "Enter" sign

    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CNumericalKeyboardWidget::returnPressed );
    gridLayout->addWidget( specialButton, 1, 3, 2, 1 );
#endif
    gridLayout->addWidget( createButton( QLatin1Char('1') ), 2, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('2') ), 2, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('3') ), 2, 2 );
    gridLayout->addWidget( createButton( QLatin1Char('0') ), 3, 0, 1, 2  );

    m_digitalButton = new CKeyboardNormalButton(this);
    connect(m_digitalButton, &CKeyboardNormalButton::clicked, this, &CNumericalKeyboardWidget::slotDigitalButtonPressed);
    gridLayout->addWidget( m_digitalButton, 3, 2 );
    m_digitalButton->setVisible(m_mode == CNumericalKeyboardWidget::Double);

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
        number.remove(0, 1);
    else
        number.prepend( QLatin1Char('-') );
    setFixedText(number);
}

void CNumericalKeyboardWidget::updateDigitalText()
{
    if (m_digitalButton) {
        m_digitalButton->setCharacter(lineEditLocale().decimalPoint());
    }
}

void CNumericalKeyboardWidget::setFixedText(const QString &text)
{
    // Reformat text correctly according to locale so convertion does not fails (and thus return 0).
    const QChar decimalSeparator = lineEditLocale().decimalPoint();
    const QChar groupSeparator = lineEditLocale().groupSeparator();
    QString fixedText = text.trimmed().remove(groupSeparator);
    const bool endsWithDecimalSeparator = fixedText.endsWith(decimalSeparator);
    QString decimals = fixedText.section(decimalSeparator, 1);

    // The latest typed decimal become the maximal one
    if (!decimals.isEmpty()) {
        while (decimals.count() > IVariable::FLOAT_PRECISION) {
            decimals.remove(decimals.length() -2, 1);
        }

        fixedText = fixedText.section(decimalSeparator, 0, 0) +decimalSeparator +decimals;
    }

    const double value = lineEditLocale().toDouble(fixedText);

    fixedText = lineEditLocale().toString(value, 'f', decimals.count());

    if (endsWithDecimalSeparator) {
        fixedText.append(decimalSeparator);
    }

    m_lineEdit->setText(fixedText);
}

void CNumericalKeyboardWidget::slotDigitalButtonPressed(QChar character)
{
    QString value = m_lineEdit->text();
    if (value.isEmpty()) {
        return;
    } else if (value.contains(character)) {
        return;
    }
    slotButtonClicked(character);
}

void CNumericalKeyboardWidget::slotBlackspaceButtonClicked(Qt::Key /*key*/)
{
    QString text = m_lineEdit->text();
    if (!text.isEmpty()) {
        text.chop(1);
        setFixedText(text);
    }
}

QLocale CNumericalKeyboardWidget::lineEditLocale() const
{
    return m_lineEdit->locale();
}
