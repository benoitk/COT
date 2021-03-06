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
const int MIN_INTEGER_VALUE = -std::numeric_limits<int>::max();
const int MAX_INTEGER_VALUE = std::numeric_limits<int>::max();
}

CNumericalKeyboardWidget::CNumericalKeyboardWidget(QWidget *parent)
    : QWidget(parent)
    , m_mode(CNumericalKeyboardWidget::Double)
{
    initializeKeyboardLayout();
}

CNumericalKeyboardWidget::CNumericalKeyboardWidget(CNumericalKeyboardWidget::Mode mode, QWidget *parent)
    : QWidget(parent)
    , m_mode(mode)
{
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

float CNumericalKeyboardWidget::floatNumber() const
{
    const QString text = m_lineEdit->text();
    const float value = lineEditLocale().toFloat(text);
    return value;
}

void CNumericalKeyboardWidget::setFloatNumber(float number, int precision)
{
    m_precision = precision;
    m_lineEdit->setText(formatFloat(number, m_precision));
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
    const float value = lineEditLocale().toFloat(text);

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
    CKeyboardNormalButton *normalButton = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    normalButton->setCharacter(character);
    connect(normalButton, &CKeyboardNormalButton::clicked, this, &CNumericalKeyboardWidget::slotButtonClicked);
    return normalButton;
}

void CNumericalKeyboardWidget::initializeKeyboardLayout()
{
    m_mainLayout = new QVBoxLayout(this);

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);

    QGridLayout* gridLayout = new QGridLayout;
    m_mainLayout->addLayout(gridLayout);

    gridLayout->addWidget( createButton( QLatin1Char('7') ), 0, 0 );
    gridLayout->addWidget( createButton( QLatin1Char('8') ), 0, 1 );
    gridLayout->addWidget( createButton( QLatin1Char('9') ), 0, 2 );
    CKeyboardSpecialButton * specialButton = new CKeyboardSpecialButton(CKeyboardButtonBase::Numeric, this);
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

    m_digitalButton = new CKeyboardNormalButton(CKeyboardButtonBase::Numeric, this);
    connect(m_digitalButton, &CKeyboardNormalButton::clicked, this, &CNumericalKeyboardWidget::slotDigitalButtonPressed);
    gridLayout->addWidget( m_digitalButton, 3, 2 );
    m_digitalButton->setVisible(m_mode == CNumericalKeyboardWidget::Double);

    specialButton = new CKeyboardSpecialButton( CKeyboardButtonBase::Numeric, this );
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
    // Reformat text correctly according to locale so conversion does not fails (and thus return 0).
    const QChar decimalSeparator = lineEditLocale().decimalPoint();
    const QChar groupSeparator = lineEditLocale().groupSeparator();
    QString fixedText = text.trimmed().remove(groupSeparator);

    if (m_mode == Integer) {
        // Use a type bigger than int, so we can compare with the max int.
        qlonglong largeValue = lineEditLocale().toLongLong(fixedText);
        if (largeValue > MAX_INTEGER_VALUE)
            return; // refuse such a large value
        if (largeValue < MIN_INTEGER_VALUE)
            return; // refuse
        fixedText = lineEditLocale().toString(largeValue);
    } else {
        const bool endsWithDecimalSeparator = fixedText.endsWith(decimalSeparator);
        QString decimals = fixedText.section(decimalSeparator, 1);

        // The latest typed decimal become the maximal one
        if (!decimals.isEmpty()) {
            while (decimals.count() > m_precision) {
                decimals.remove(decimals.length() -2, 1);
            }

            fixedText = fixedText.section(decimalSeparator, 0, 0) +decimalSeparator +decimals;
        }

        const float value = lineEditLocale().toFloat(fixedText);
        const double doubleValue = lineEditLocale().toDouble(fixedText);

        fixedText = lineEditLocale().toString(value, 'f', decimals.count());

        // Check if we're not hitting the limits of the "float" precision,
        // by comparing with what we would get with a "double".
        const QString fixedTextFromDouble = lineEditLocale().toString(doubleValue, 'f', decimals.count());
        if (fixedText != fixedTextFromDouble) {
            return; // refuse adding a digit that would lead to unwanted changes for lack of precision
        }

        if (endsWithDecimalSeparator) {
            fixedText.append(decimalSeparator);
        }
    }

    m_lineEdit->setText(fixedText);
}

QString CNumericalKeyboardWidget::formatFloat(float value, int maxDecimals) const
{
    QString str = lineEditLocale().toString(value, 'f', maxDecimals);
    // Remove trailing zeros after the decimal point
    const int dot = str.indexOf(lineEditLocale().decimalPoint());
    if (dot > -1) {
        while (str.endsWith('0'))
            str.chop(1);
        if (dot == str.length() - 1)
            str.chop(1); // remove lone trailing dot
    }
    return str;
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
