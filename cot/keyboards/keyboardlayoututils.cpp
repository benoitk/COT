#include "keyboardlayoututils.h"

// Keyboard layout: one string per row.
// First character is the letter, second letter is the width.
// Special letter codes: B=backspace  T=tab  C=caps  R=enter  S=shift
// Special width codes: A space means 2, the default width.
QStringList KeyboardLayoutUtils::frenchKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("² & é \" ' ( - è _ ç à ) = B3" )
                                          << QStringLiteral("T3a z e r t y u i o p ^ $" )
                                          << QStringLiteral("C4q s d f g h j k l m ù * R3" )
                                          << QStringLiteral("S5< w x c v b n , ; : ! S4" );
    return lst;
}


QStringList KeyboardLayoutUtils::russianKeyboardLayout()
{
    return QStringList();
}


QStringList KeyboardLayoutUtils::englishKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("` 1 2 3 4 5 6 7 8 9 0 - = B3" )
                                          << QStringLiteral("T3q w e r t y u i o p [ ] \\ " )
                                          << QStringLiteral("C4a s d f g h j k l ; \" R3" )
                                          << QStringLiteral("S5z x c v b n m , . / S4" );
    return lst;
}


QStringList KeyboardLayoutUtils::spanishKeyboardLayout()
{
    return QStringList();
}


QStringList KeyboardLayoutUtils::portugueseKeyboardLayout()
{
    return QStringList();
}


QStringList KeyboardLayoutUtils::chineseKeyboardLayout()
{
    return QStringList();
}

QChar KeyboardLayoutUtils::convertToUpper(QChar currentChar, const QString &shiftMappingString)
{
    for( int i = 0; i+1 < shiftMappingString.size(); i += 2 ) {
        if( shiftMappingString[i] == currentChar )
            return shiftMappingString[i+1];
    }
    return currentChar.toUpper();
}

QChar KeyboardLayoutUtils::convertToLower(QChar currentChar, const QString &shiftMappingString)
{
    for( int i = 0; i+1 < shiftMappingString.size(); i += 2 ) {
        if( shiftMappingString[i+1] == currentChar )
            return shiftMappingString[i];
    }
    return currentChar.toLower();
}


QString KeyboardLayoutUtils::frenchShiftMapping()
{
    return QStringLiteral("&1é2\"3'4(5-6è7_8ç9à0)°=+");
}


QString KeyboardLayoutUtils::russianShiftMapping()
{
    //TODO
    return QString();
}


QString KeyboardLayoutUtils::englishShiftMapping()
{
    return QStringLiteral("1!2@3#4$5%6^7&8*9(0)-_=+[{]};:'\",<.>/?`~");
}


QString KeyboardLayoutUtils::spanishShiftMapping()
{
    //TODO
    return QString();
}


QString KeyboardLayoutUtils::portugueseShiftMapping()
{
    //TODO
    return QString();
}


QString KeyboardLayoutUtils::chineseShiftMapping()
{
    //TODO
    return QString();
}
