#include "keyboarddialog.h"
#include "keyboardlayoututils.h"
#include "keyboardnormalbutton.h"
#include "keyboardspecialbutton.h"
#include <QGridLayout>
#include <QLocale>
#include <QLineEdit>

KeyboardDialog::KeyboardDialog(QWidget *parent)
    : QDialog(parent),
      mKeyboardLayout(0),
      mMainLayout(0),
      mCapsLockOn(false),
      mShiftOn(false)
{
    mMainLayout = new QVBoxLayout(this);
    mLineEdit = new QLineEdit;
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mMainLayout->addWidget(mLineEdit);
    initializeKeyboardLayout();
}

KeyboardDialog::~KeyboardDialog()
{

}

void KeyboardDialog::initializeKeyboardLayout()
{
    delete mKeyboardLayout;
    mKeyboardLayout = new QGridLayout;
    QLocale loc = locale();
    const QStringList listLanguage = loc.uiLanguages();

    QStringList keyboardLayout;
    //TODO verify lang.
    Q_FOREACH( const QString &lang, listLanguage) {
        if (lang == QStringLiteral("fr")) {
            keyboardLayout = KeyboardLayoutUtils::frenchKeyboardLayout();
            break;
        } else if (lang == QStringLiteral("en")) {
            keyboardLayout = KeyboardLayoutUtils::englishKeyboardLayout();
            break;
        } else if (lang == QStringLiteral("ch")) {
            keyboardLayout = KeyboardLayoutUtils::chineseKeyboardLayout();
        }
        //TODO add more keyboard layout
    }

    //Fallback to french keyboard
    if (keyboardLayout.isEmpty()) {
        keyboardLayout = KeyboardLayoutUtils::frenchKeyboardLayout();
    }

    mMainLayout->addLayout(mKeyboardLayout);
    int cellY = 0;
    Q_FOREACH(const QString &rowLayout, keyboardLayout) {
        int cellX = 0;
        for (int i = 0; i < rowLayout.size(); i += 2) {
            const QChar charValue = rowLayout[i];
            const QChar widthValue = rowLayout[i+1];
            const int cellWidth = widthValue == ' ' ? 2 : widthValue.toLatin1() - '0';
            KeyboardButtonBase* button = 0;
            if (charValue.isUpper()) {
                // special char
                KeyboardSpecialButton* specialButton = 0;
                if( charValue == QLatin1Char( 'T' ) ) { // tab
                    // TODO: what does Tab do? We can't enter \t into lineedits.
                    KeyboardNormalButton* charButton = new KeyboardNormalButton( this );
                    charButton->setText( tr( "Tab" ) );
                    button = charButton;
                } else if( charValue == QLatin1Char( 'R' ) ) { // enter
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Enter" ) );
                    // make Enter do the same as OK
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &QDialog::accept );
                } else if( charValue == QLatin1Char( 'S' ) ) { // shift
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Shift" ) );
                    specialButton->setSpecialKey( Qt::Key_Shift );
                    specialButton->setCheckable( true );
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardDialog::slotShiftToggled );
                    mShiftButtons.append( specialButton );
                } else if( charValue == QLatin1Char( 'C' ) ) { // capslock
                    specialButton = new KeyboardSpecialButton( this );
                    specialButton->setText( tr( "Caps" ) );
                    specialButton->setSpecialKey( Qt::Key_CapsLock );
                    specialButton->setCheckable( true );
                    connect( specialButton, &KeyboardSpecialButton::clicked, this, &KeyboardDialog::slotCapsLockToggled );
                } else if( charValue == QChar( 'B' ) ) { // backspace
                    //TODO
                } else {
                    qDebug( "Unknown special char %d", charValue.toLatin1() );
                }
                if ( specialButton )
                    button = specialButton;
            }  else {
                KeyboardNormalButton* charButton = new KeyboardNormalButton( this );
                charButton->setCharacter(charValue);
                button = charButton;
            }

            if ( button ) {
                mKeyboardLayout->addWidget( button, cellY, cellX, 1, cellWidth );
                button->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ) );
            }
            cellX += cellWidth;
        }
        ++cellY;
    }
}

void KeyboardDialog::slotShiftToggled()
{
    mShiftOn = !mShiftOn;
    //Synchronize shift button.
    Q_FOREACH(KeyboardSpecialButton *button, mShiftButtons) {
        button->setChecked(mShiftOn);
    }
}

void KeyboardDialog::slotCapsLockToggled()
{

}
