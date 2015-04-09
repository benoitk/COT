#include "keyboardnormalbutton.h"
#include "keyboardwidget.h"
#include "keyboardlayoututils.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QLocale>
#include <QVBoxLayout>
#include <qlineedit.h>
#include <QApplication>

KeyboardWidget::KeyboardWidget(QWidget *parent)
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

KeyboardWidget::~KeyboardWidget()
{

}

bool KeyboardWidget::event(QEvent *ev)
{
    if (ev->type() == QEvent::LocaleChange) {
        initializeKeyboardLayout();
        return true;
    }
    return QWidget::event(ev);
}

void KeyboardWidget::initializeKeyboardLayout()
{
    delete m_keyboardLayout;
    m_keyboardLayout = new QGridLayout;
    QLocale loc = locale();
    const QStringList listLanguage = loc.uiLanguages();

    QStringList keyboardLayout;
    //TODO verify lang.
    Q_FOREACH( const QString &lang, listLanguage) {
        if (lang == QStringLiteral("fr")) {
            keyboardLayout = KeyboardLayoutUtils::frenchKeyboardLayout();
            m_currentLanguage = lang;
            break;
        } else if (lang == QStringLiteral("en")) {
            keyboardLayout = KeyboardLayoutUtils::englishKeyboardLayout();
            m_currentLanguage = lang;
            break;
        } else if (lang == QStringLiteral("ch")) {
            keyboardLayout = KeyboardLayoutUtils::chineseKeyboardLayout();
            m_currentLanguage = lang;
        }
        //TODO add more keyboard layout
    }

    //Fallback to french keyboard
    if (keyboardLayout.isEmpty()) {
        keyboardLayout = KeyboardLayoutUtils::frenchKeyboardLayout();
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
            KeyboardButtonBase* button = 0;
            if (charValue.isUpper()) {
                // special char
                KeyboardSpecialButton* specialButton = 0;
                if( charValue == QLatin1Char( 'T' ) ) { // tab
                    // TODO: what does Tab do? We can't enter \t into lineedits.
                    KeyboardNormalButton* normalButton = new KeyboardNormalButton( this );
                    normalButton->setCharacter(QLatin1Char('\t'));
                    normalButton->setText( tr( "Tab" ) );
                    button = normalButton;
                    m_normalButtons << normalButton;
                } else if( charValue == QLatin1Char( 'R' ) ) { // enter
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Enter" ) );
                    // make Enter do the same as OK
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardWidget::returnPressed );
                } else if( charValue == QLatin1Char( 'S' ) ) { // shift
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Shift" ) );
                    specialButton->setSpecialKey( Qt::Key_Shift );
                    specialButton->setCheckable( true );
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardWidget::slotShiftToggled );
                    m_shiftButtons.append( specialButton );
                } else if( charValue == QLatin1Char( 'C' ) ) { // capslock
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Caps" ) );
                    specialButton->setSpecialKey( Qt::Key_CapsLock );
                    specialButton->setCheckable( true );
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardWidget::slotCapsLockToggled );
                } else if( charValue == QLatin1Char( 'B' ) ) { // backspace
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( QChar(0x2190) );
                    specialButton->setSpecialKey( Qt::Key_Backspace );
                    connect(specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardWidget::slotSpecialButtonClicked);
                } else {
                    qDebug( "Unknown special char %d", charValue.toLatin1() );
                }
                if ( specialButton ) {
                    button = specialButton;
                }
            }  else {
                KeyboardNormalButton* normalButton = new KeyboardNormalButton( this );
                connect(normalButton, &KeyboardNormalButton::clicked, this, &KeyboardWidget::slotButtonClicked);
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
        KeyboardNormalButton* spaceButton = new KeyboardNormalButton( this );
        connect(spaceButton, &KeyboardNormalButton::clicked, this, &KeyboardWidget::slotButtonClicked);
        spaceButton->setCharacter(QLatin1Char(' '));
        spaceButton->setText(tr("Space"));
        m_keyboardLayout->addWidget( spaceButton, cellY, 1, 1, maxColumn - 2 );
    }
}

void KeyboardWidget::slotShiftToggled()
{
    m_shiftOn = !m_shiftOn;
    //Synchronize shift button.
    Q_FOREACH(KeyboardSpecialButton *button, m_shiftButtons) {
        button->setChecked(m_shiftOn);
    }
    slotCapsLockToggled();
}

void KeyboardWidget::slotCapsLockToggled()
{
    m_capsLockOn = !m_capsLockOn;
    QString shiftMapping;

    if (m_currentLanguage == QStringLiteral("fr")) {
        shiftMapping = KeyboardLayoutUtils::frenchShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("en")) {
        shiftMapping = KeyboardLayoutUtils::englishShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("ch")) {
        shiftMapping = KeyboardLayoutUtils::chineseShiftMapping();
    } else {
        shiftMapping = KeyboardLayoutUtils::frenchShiftMapping();
    }
    //TODO add more


    Q_FOREACH(KeyboardNormalButton *normalButton, m_normalButtons) {
        const QChar currentChar = normalButton->character();
        //We don't change tab value :)
        if ( currentChar == '\t' )
            continue;
        if ( m_capsLockOn )
            normalButton->setCharacter( KeyboardLayoutUtils::convertToUpper(currentChar, shiftMapping) );
        else
            normalButton->setCharacter( KeyboardLayoutUtils::convertToLower(currentChar, shiftMapping) );
    }
}


void KeyboardWidget::slotButtonClicked(const QChar &character)
{
    m_lineEdit->setText(m_lineEdit->text().append(character));
    keyClicked();
    m_lineEdit->setFocus();
}

void KeyboardWidget::slotSpecialButtonClicked(Qt::Key key)
{
    QKeyEvent ev( QEvent::KeyPress, key, 0 /*keyState*/, QString() );
    qApp->sendEvent( m_lineEdit, &ev );
    m_lineEdit->setFocus();
}

void KeyboardWidget::keyClicked()
{
    // Any key pressed after shift, reverts to normal
    if ( m_shiftOn ) {
        Q_FOREACH(KeyboardNormalButton *normalButton, m_normalButtons) {
            normalButton->setChecked( false );
        }
        m_shiftOn = false;
        slotCapsLockToggled();
    }
}
