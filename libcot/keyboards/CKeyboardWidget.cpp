#include "CKeyboardNormalButton.h"
#include "CKeyboardWidget.h"
#include "CKeyboardLayoutUtils.h"
#include "CKeyboardSpecialButton.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QLocale>
#include <QVBoxLayout>
#include <qlineedit.h>
#include <QApplication>

CKeyboardWidget::CKeyboardWidget(QWidget *parent)
    : QWidget(parent),
      m_keyboardLayout(0),
      m_mainLayout(0),
      m_capsLockOn(false),
      m_shiftOn(false)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setMargin(0);

    m_lineEdit = new QLineEdit;
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    m_lineEdit->setReadOnly(true);
    initializeKeyboardLayout();
}

CKeyboardWidget::~CKeyboardWidget()
{

}

QString CKeyboardWidget::text() const
{
    return m_lineEdit->text();
}

bool CKeyboardWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::LocaleChange || ev->type() == QEvent::LanguageChange) {
        changeKeyboardLayout();
        return true;
    }
    return QWidget::event(ev);
}

void CKeyboardWidget::changeKeyboardLayout()
{
    initializeKeyboardLayout();
}

void CKeyboardWidget::initializeKeyboardLayout()
{
    delete m_keyboardLayout;
    m_keyboardLayout = new QGridLayout;
    QLocale loc = locale();
    const QStringList listLanguage = loc.uiLanguages();

    QStringList keyboardLayout;
    //TODO verify lang.
    Q_FOREACH( const QString &lang, listLanguage) {
        if (lang == QStringLiteral("fr")) {
            keyboardLayout = CKeyboardLayoutUtils::frenchKeyboardLayout();
            m_currentLanguage = lang;
            break;
        } else if (lang == QStringLiteral("en")) {
            keyboardLayout = CKeyboardLayoutUtils::englishKeyboardLayout();
            m_currentLanguage = lang;
            break;
        } else if (lang == QStringLiteral("ch")) {
            keyboardLayout = CKeyboardLayoutUtils::chineseKeyboardLayout();
            m_currentLanguage = lang;
            break;
        }
        //TODO add more keyboard layout
    }

    //Fallback to french keyboard
    if (keyboardLayout.isEmpty()) {
        keyboardLayout = CKeyboardLayoutUtils::frenchKeyboardLayout();
        m_currentLanguage = QStringLiteral("fr");
    }

    if (keyboardLayout.isEmpty()) {
        qDebug() << "Missing keyboard layout definition";
    }

    m_mainLayout->addLayout(m_keyboardLayout);
    int cellY = 0;
    int maxColumn = 0;
    Q_FOREACH(const QString &rowLayout, keyboardLayout) {
        int cellX = 0;
        for (int i = 0; i+1 < rowLayout.size(); i += 2) {
            const QChar charValue = rowLayout[i];
            const QChar widthValue = rowLayout[i+1];
            const int cellWidth = widthValue == ' ' ? 2 : widthValue.toLatin1() - '0';
            CKeyboardButtonBase* button = 0;
            if (charValue.isUpper()) {
                // special char
                CKeyboardSpecialButton* specialButton = 0;
                if( charValue == QLatin1Char( 'T' ) ) { // tab
                    // TODO: what does Tab do? We can't enter \t into lineedits.
                    CKeyboardNormalButton* normalButton = new CKeyboardNormalButton( this );
                    normalButton->setCharacter(QLatin1Char('\t'));
                    normalButton->setText( tr( "Tab" ) );
                    button = normalButton;
                    m_normalButtons << normalButton;
                } else if( charValue == QLatin1Char( 'R' ) ) { // enter
                    specialButton = new CKeyboardSpecialButton( this );
                    specialButton->setText( tr( "Enter" ) );
                    // make Enter do the same as OK
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::returnPressed );
                } else if( charValue == QLatin1Char( 'S' ) ) { // shift
                    specialButton = new CKeyboardSpecialButton( this );
                    specialButton->setText( tr( "Shift" ) );
                    specialButton->setSpecialKey( Qt::Key_Shift );
                    specialButton->setCheckable( true );
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::slotShiftToggled );
                    m_shiftButtons.append( specialButton );
                } else if( charValue == QLatin1Char( 'C' ) ) { // capslock
                    specialButton = new CKeyboardSpecialButton( this );
                    specialButton->setText( tr( "Caps" ) );
                    specialButton->setSpecialKey( Qt::Key_CapsLock );
                    specialButton->setCheckable( true );
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::slotCapsLockToggled );
                } else if( charValue == QLatin1Char( 'B' ) ) { // backspace
                    specialButton = new CKeyboardSpecialButton( this );
                    specialButton->setText( QChar(0x2190) );
                    specialButton->setSpecialKey( Qt::Key_Backspace );
                    connect(specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::slotSpecialButtonClicked);
                } else {
                    qDebug( "Unknown special char %d", charValue.toLatin1() );
                }
                if ( specialButton ) {
                    button = specialButton;
                }
            }  else {
                CKeyboardNormalButton* normalButton = new CKeyboardNormalButton( this );
                connect(normalButton, &CKeyboardNormalButton::clicked, this, &CKeyboardWidget::slotButtonClicked);
                normalButton->setCharacter(charValue);
                m_normalButtons << normalButton;
                button = normalButton;
            }

            if ( button ) {
                m_keyboardLayout->addWidget( button, cellY, cellX, 1, cellWidth );
                button->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ) );
            }
            cellX += cellWidth;
        }
        maxColumn = qMax(maxColumn, cellX);
        ++cellY;
    }
    if ( maxColumn > 0 ) {
        //Add Space bar.
        CKeyboardNormalButton* spaceButton = new CKeyboardNormalButton( this );
        connect(spaceButton, &CKeyboardNormalButton::clicked, this, &CKeyboardWidget::slotButtonClicked);
        spaceButton->setCharacter(QLatin1Char(' '));
        spaceButton->setText(tr("Space"));
        m_keyboardLayout->addWidget( spaceButton, cellY, 1, 1, maxColumn - 2 );
    }
}

void CKeyboardWidget::slotShiftToggled()
{
    m_shiftOn = !m_shiftOn;
    //Synchronize shift button.
    Q_FOREACH(CKeyboardSpecialButton *button, m_shiftButtons) {
        button->setChecked(m_shiftOn);
    }
    slotCapsLockToggled();
}

void CKeyboardWidget::slotCapsLockToggled()
{
    m_capsLockOn = !m_capsLockOn;
    QString shiftMapping;

    if (m_currentLanguage == QStringLiteral("fr")) {
        shiftMapping = CKeyboardLayoutUtils::frenchShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("en")) {
        shiftMapping = CKeyboardLayoutUtils::englishShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("ch")) {
        shiftMapping = CKeyboardLayoutUtils::chineseShiftMapping();
    } else {
        shiftMapping = CKeyboardLayoutUtils::frenchShiftMapping();
    }
    //TODO add more


    Q_FOREACH(CKeyboardNormalButton *normalButton, m_normalButtons) {
        const QChar currentChar = normalButton->character();
        //We don't change tab value :)
        if ( currentChar == '\t' )
            continue;
        if ( m_capsLockOn )
            normalButton->setCharacter( CKeyboardLayoutUtils::convertToUpper(currentChar, shiftMapping) );
        else
            normalButton->setCharacter( CKeyboardLayoutUtils::convertToLower(currentChar, shiftMapping) );
    }
}


void CKeyboardWidget::slotButtonClicked(const QChar &character)
{
    m_lineEdit->setText(m_lineEdit->text().append(character));
    keyClicked();
    m_lineEdit->setFocus();
}

void CKeyboardWidget::slotSpecialButtonClicked(Qt::Key key)
{
    QKeyEvent ev( QEvent::KeyPress, key, 0 /*keyState*/, QString() );
    qApp->sendEvent( m_lineEdit, &ev );
    m_lineEdit->setFocus();
}

void CKeyboardWidget::keyClicked()
{
    // Any key pressed after shift, reverts to normal
    if ( m_shiftOn ) {
        Q_FOREACH(CKeyboardNormalButton *normalButton, m_normalButtons) {
            normalButton->setChecked( false );
        }
        m_shiftOn = false;
        slotCapsLockToggled();
    }
}
