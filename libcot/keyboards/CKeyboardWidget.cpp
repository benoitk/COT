#include "CKeyboardNormalButton.h"
#include "CKeyboardWidget.h"
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
    m_lineEdit->setFocusPolicy(Qt::NoFocus);
    m_lineEdit->setObjectName(QStringLiteral("lineedit"));
    m_mainLayout->addWidget(m_lineEdit);
    initializeKeyboardLayout();
}

CKeyboardWidget::~CKeyboardWidget()
{

}

QString CKeyboardWidget::text() const
{
    return m_lineEdit->text();
}

void CKeyboardWidget::setText(const QString &text)
{
    m_lineEdit->setText(text);
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
    clearDeadKey();
    delete m_keyboardLayout;
    m_keyboardLayout = new QGridLayout;
    QLocale loc = locale();
    const QStringList listLanguage = loc.uiLanguages();
    //qDebug()<<" listLanguage"<<listLanguage;
    QStringList keyboardLayout;
    foreach( const QString &lang, listLanguage) {
        if (lang.startsWith(QLatin1String("fr"))) {
            keyboardLayout = utils.frenchKeyboardLayout();
            m_currentLanguage = QStringLiteral("fr_FR");
            break;
        } else if (lang.startsWith(QLatin1String("en")) || lang == QLatin1String("C")) {
            keyboardLayout = utils.englishKeyboardLayout();
            m_currentLanguage = QStringLiteral("en_GB");
            break;
        } else if (lang.startsWith(QLatin1String("zh"))) {
            keyboardLayout = utils.chineseKeyboardLayout();
            m_currentLanguage = QStringLiteral("zh");
            break;
        } else if (lang.startsWith(QLatin1String("ru"))) {
            keyboardLayout = utils.russianKeyboardLayout();
            m_currentLanguage = QStringLiteral("ru");
            break;
        } else if (lang.startsWith(QLatin1String("es"))) {
            keyboardLayout = utils.spanishKeyboardLayout();
            m_currentLanguage = QStringLiteral("es");
            break;
        } else if (lang.startsWith(QLatin1String("pt"))) {
            keyboardLayout = utils.portugueseKeyboardLayout();
            m_currentLanguage = QStringLiteral("pt");
            break;
        }
    }

    //Fallback to french keyboard
    if (keyboardLayout.isEmpty()) {
        keyboardLayout = utils.frenchKeyboardLayout();
        m_currentLanguage = QStringLiteral("fr_FR");
    }

    if (keyboardLayout.isEmpty()) {
        qDebug() << "Missing keyboard layout definition";
    }

    m_mainLayout->addLayout(m_keyboardLayout);
    int cellY = 0;
    int maxColumn = 0;
    foreach(const QString &rowLayout, keyboardLayout) {
        int cellX = 0;
        for (int i = 0; i+1 < rowLayout.size(); i += 2) {
            const QChar charValue = rowLayout[i];
            const QChar widthValue = rowLayout[i+1];
            const int cellWidth = widthValue == QLatin1Char(' ') ? 2 : qMax((widthValue.toLatin1() - '0'), 2);
            CKeyboardButtonBase* button = 0;
            if (charValue.isUpper()) {
                CKeyboardSpecialButton* specialButton = 0;
                if( charValue == QLatin1Char( 'T' ) ) { // tab
                    CKeyboardNormalButton* normalButton = new CKeyboardNormalButton( CKeyboardButtonBase::Alpha, this );
                    normalButton->setCharacter(QLatin1Char('\t'));
                    normalButton->setText( tr( "Tab" ) );
                    button = normalButton;
                    m_normalButtons << normalButton;
#if 0
                } else if( charValue == QLatin1Char( 'R' ) ) { // enter
                    specialButton = new CKeyboardSpecialButton( this );
                    specialButton->setText( tr( "Enter" ) );
                    // make Enter do the same as OK
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::returnPressed );
#endif
                } else if( charValue == QLatin1Char( 'S' ) ) { // shift
                    specialButton = new CKeyboardSpecialButton( CKeyboardButtonBase::Alpha, this );
                    specialButton->setText( tr( "Shift" ) );
                    specialButton->setSpecialKey( Qt::Key_Shift );
                    specialButton->setCheckable( true );
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::slotShiftToggled );
                    m_shiftButtons.append( specialButton );
                } else if( charValue == QLatin1Char( 'C' ) ) { // capslock
                    specialButton = new CKeyboardSpecialButton( CKeyboardButtonBase::Alpha, this );
                    specialButton->setText( tr( "Caps" ) );
                    specialButton->setSpecialKey( Qt::Key_CapsLock );
                    specialButton->setCheckable( true );
                    connect( specialButton, &CKeyboardSpecialButton::clicked, this, &CKeyboardWidget::slotCapsLockToggled );
                } else if( charValue == QLatin1Char( 'B' ) ) { // backspace
                    specialButton = new CKeyboardSpecialButton( CKeyboardButtonBase::Alpha, this );
                    specialButton->setAutoRepeat(true);
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
                CKeyboardNormalButton* normalButton = new CKeyboardNormalButton( CKeyboardButtonBase::Alpha, this );
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
        CKeyboardNormalButton* spaceButton = new CKeyboardNormalButton( CKeyboardButtonBase::Alpha, this );
        connect(spaceButton, &CKeyboardNormalButton::clicked, this, &CKeyboardWidget::slotButtonClicked);
        spaceButton->setCharacter(QLatin1Char(' '));
        spaceButton->setText(tr("Space"));
        m_keyboardLayout->addWidget( spaceButton, cellY, 1, 1, maxColumn - 2 );
    }
    keyClicked();
}

void CKeyboardWidget::slotShiftToggled()
{
    m_shiftOn = !m_shiftOn;
    //Synchronize shift button.
    foreach(CKeyboardSpecialButton *button, m_shiftButtons) {
        button->setChecked(m_shiftOn);
    }
    slotCapsLockToggled();
}

void CKeyboardWidget::slotCapsLockToggled()
{
    m_capsLockOn = !m_capsLockOn;
    QString shiftMapping;

    if (m_currentLanguage == QStringLiteral("fr_FR")) {
        shiftMapping = utils.frenchShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("en_GB")) {
        shiftMapping = utils.englishShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("zh")) {
        shiftMapping = utils.chineseShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("ru")) {
        shiftMapping = utils.russianShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("es")) {
        shiftMapping = utils.spanishShiftMapping();
    } else if (m_currentLanguage == QStringLiteral("pt")) {
        shiftMapping = utils.portugueseShiftMapping();
    } else {
        shiftMapping = utils.frenchShiftMapping();
    }

    foreach(CKeyboardNormalButton *normalButton, m_normalButtons) {
        const QChar currentChar = normalButton->character();
        //We don't change tab value :)
        if ( currentChar == QLatin1Char('\t') )
            continue;
        if ( m_capsLockOn )
            normalButton->setCharacter( utils.convertToUpper(currentChar, shiftMapping) );
        else
            normalButton->setCharacter( utils.convertToLower(currentChar, shiftMapping) );
    }
}

void CKeyboardWidget::clearDeadKey()
{
    m_deadKey.clear();
}

void CKeyboardWidget::slotButtonClicked(const QChar &character)
{
    QString newCharacter = QString(character);
    // trema is a QString not a unique charactere.
    if ((!utils.isADeadKey(m_deadKey)) && (character == (QString(QLatin1String("¨")).at(1)) || utils.isADeadKey(character))) {
        m_deadKey = newCharacter;
        return;
    } else {
        if (!m_deadKey.isEmpty()) {
            if (m_deadKey.at(0) == QString(QLatin1Literal("¨")).at(1)) {
                newCharacter = utils.convertDeadKey(m_deadKey.at(0), newCharacter);
            } else {
                newCharacter = utils.convertDeadKey(m_deadKey, newCharacter);
            }
        }
        clearDeadKey();
    }
    QKeyEvent ev = QKeyEvent( QEvent::KeyPress, 0 /*key not needed*/, 0 /*keyState()*/, newCharacter );
    qApp->sendEvent( m_lineEdit, &ev );
    keyClicked();
}

void CKeyboardWidget::slotSpecialButtonClicked(Qt::Key key)
{
    QKeyEvent ev( QEvent::KeyPress, key, 0 /*keyState*/, QString() );
    qApp->sendEvent( m_lineEdit, &ev );
}

void CKeyboardWidget::keyClicked()
{
    // Any key pressed after shift, reverts to normal
    if ( m_shiftOn ) {
        foreach(CKeyboardNormalButton *normalButton, m_normalButtons) {
            normalButton->setChecked( false );
        }
        m_shiftOn = false;
        foreach(CKeyboardSpecialButton *button, m_shiftButtons) {
            button->setChecked(m_shiftOn);
        }
        slotCapsLockToggled();
    }
}
