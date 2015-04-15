#include "CKeyboardLayoutUtils.h"

//See http://fr.wikipedia.org/wiki/Disposition_des_touches_des_claviers_informatiques

// Keyboard layout: one string per row.
// First character is the letter, second letter is the width.
// Special letter codes: B=backspace  T=tab  C=caps  R=enter  S=shift
// Special width codes: A space means 2, the default width.
QStringList CKeyboardLayoutUtils::frenchKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("² & é \" ' ( - è _ ç à ) = B3" )
                                          << QStringLiteral("T3a z e r t y u i o p ^ $ " )
                                          << QStringLiteral("C4q s d f g h j k l m ù * R3" )
                                          << QStringLiteral("S5< w x c v b n , ; : ! S4" );
    return lst;
}


QStringList CKeyboardLayoutUtils::russianKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("1 2 3 4 5 6 7 8 9 0 _ = \\ B3")
                                          << QStringLiteral("T3й ц у к е н г ш щ з х ъ ")
                                          << QStringLiteral("C4ф ы в а п р о л д ж э R3")
                                          << QStringLiteral("S5я ч с м и т ь б ю . S4");
    return lst;
}


QStringList CKeyboardLayoutUtils::englishKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("` 1 2 3 4 5 6 7 8 9 0 - = B3" )
                                          << QStringLiteral("T3q w e r t y u i o p [ ] \\ " )
                                          << QStringLiteral("C4a s d f g h j k l ; \" R3" )
                                          << QStringLiteral("S5z x c v b n m , . / S4" );
    return lst;
}


QStringList CKeyboardLayoutUtils::spanishKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("² 1 2 3 4 5 6 7 8 9 0 ' ¡ B3")
                                          << QStringLiteral("T3q w e r t y u i o p [ ] ")
                                          << QStringLiteral("C4a s d f g h j k l ň { } R3")
                                          << QStringLiteral("S5< w x c v b n m , . _ S4");

    return lst;
}


QStringList CKeyboardLayoutUtils::portugueseKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("\\ 1 2 3 4 5 6 7 8 9 0 \" B3" )
                                          << QStringLiteral("T3q w e r t y u i o p + ` ")
                                          << QStringLiteral("C4a s d f g h j k l ç ~ R3")
                                          << QStringLiteral("S5< z x c v b n m , . _ S4");
    return lst;
}


QStringList CKeyboardLayoutUtils::chineseKeyboardLayout()
{
    const QStringList lst = QStringList() << QStringLiteral("' 1 2 3 4 5 6 7 8 9 0 _ = \\ B3")
                                          << QStringLiteral("T3q w e r t y u i o p [ ] ")
                                          << QStringLiteral("C4a s d f g h j k l ; , R3")
                                          << QStringLiteral("S5z x c v b n m , . / S4");
    return lst;
}

QChar CKeyboardLayoutUtils::convertToUpper(QChar currentChar, const QString &shiftMappingString)
{
    for( int i = 0; i+1 < shiftMappingString.size(); i += 2 ) {
        if( shiftMappingString[i] == currentChar )
            return shiftMappingString[i+1];
    }
    return currentChar.toUpper();
}

QChar CKeyboardLayoutUtils::convertToLower(QChar currentChar, const QString &shiftMappingString)
{
    for( int i = 0; i+1 < shiftMappingString.size(); i += 2 ) {
        if( shiftMappingString[i+1] == currentChar )
            return shiftMappingString[i];
    }
    return currentChar.toLower();
}


QString CKeyboardLayoutUtils::frenchShiftMapping()
{
    return QStringLiteral("&1é2\"3'4(5-6è7_8ç9à0)°=+<>:/;.,?^¨");
}


QString CKeyboardLayoutUtils::russianShiftMapping()
{
    return QStringLiteral("1!2\"3И4;5%6:7?8*9(0)_-=+\\/");
}


QString CKeyboardLayoutUtils::englishShiftMapping()
{
    return QStringLiteral("1!2@3#4$5%6^7&8*9(0)-_=+[{]};:'\",<.>/?`~");
}


QString CKeyboardLayoutUtils::spanishShiftMapping()
{
    return QStringLiteral("1!2\"3.4$5%6&7/8(9)0=.?");
}


QString CKeyboardLayoutUtils::portugueseShiftMapping()
{
    return QStringLiteral("\\|1!2\"3#4$5%6&7/8(9]0='?");
}


QString CKeyboardLayoutUtils::chineseShiftMapping()
{
    //TODO
    return QString();
}
