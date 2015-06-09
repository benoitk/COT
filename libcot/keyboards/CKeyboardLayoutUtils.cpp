#include "CKeyboardLayoutUtils.h"
#include <QHash>
#include <QDebug>
//See http://fr.wikipedia.org/wiki/Disposition_des_touches_des_claviers_informatiques

// Keyboard layout: one string per row.
// First character is the letter, second letter is the width.
// Special letter codes: B=backspace  T=tab  C=caps  R=enter  S=shift
// Special width codes: A space means 2, the default width.
CKeyboardLayoutUtils::CKeyboardLayoutUtils()
{
    QHash<QString, QString> trema;
    trema.insert(QLatin1Literal("e"), QString::fromUtf8("ë"));
    trema.insert(QLatin1Literal("o"), QString::fromUtf8("ö"));
    trema.insert(QLatin1Literal("u"), QString::fromUtf8("ü"));
    trema.insert(QLatin1Literal("y"), QString::fromUtf8("ÿ"));
    hashKeys.insert(QString::fromUtf8("¨"), trema);

    QHash<QString, QString> caret;
    caret.insert(QLatin1Literal("e"), QString::fromUtf8("ê"));
    caret.insert(QLatin1Literal("o"), QString::fromUtf8("ô"));
    caret.insert(QLatin1Literal("u"), QString::fromUtf8("û"));
    caret.insert(QLatin1Literal("y"), QString::fromUtf8("ŷ"));
    hashKeys.insert(QLatin1Literal("^"), caret);

    QHash<QString, QString> tilde;
    tilde.insert(QLatin1Literal("o"), QString::fromUtf8("õ"));
    tilde.insert(QLatin1Literal("n"), QString::fromUtf8("ñ"));
    tilde.insert(QLatin1Literal("a"), QString::fromUtf8("ã"));
    hashKeys.insert(QLatin1Literal("~"), tilde);

}

QStringList CKeyboardLayoutUtils::frenchKeyboardLayout() const
{
    const QStringList lst = QStringList() << QStringLiteral("² & é \" ' ( - è _ ç à ) = B3" )
                                          << QStringLiteral("T3a z e r t y u i o p ^ $ " )
                                          << QStringLiteral("C4q s d f g h j k l m ù * R3" )
                                          << QStringLiteral("S5< w x c v b n , ; : ! S4" );
    return lst;
}


QStringList CKeyboardLayoutUtils::russianKeyboardLayout() const
{
    const QStringList lst = QStringList() << QStringLiteral("1 2 3 4 5 6 7 8 9 0 _ = \\ B3")
                                          << QStringLiteral("T3й ц у к е н г ш щ з х ъ ")
                                          << QStringLiteral("C4ф ы в а п р о л д ж э R3")
                                          << QStringLiteral("S5я ч с м и т ь б ю . S4");
    return lst;
}


QStringList CKeyboardLayoutUtils::englishKeyboardLayout() const
{
    const QStringList lst = QStringList() << QStringLiteral("` 1 2 3 4 5 6 7 8 9 0 - = B3" )
                                          << QStringLiteral("T3q w e r t y u i o p [ ] \\ " )
                                          << QStringLiteral("C4a s d f g h j k l ; \" R3" )
                                          << QStringLiteral("S5z x c v b n m , . / S4" );
    return lst;
}


QStringList CKeyboardLayoutUtils::spanishKeyboardLayout() const
{
    const QStringList lst = QStringList() << QStringLiteral("² 1 2 3 4 5 6 7 8 9 0 ' ¡ B3")
                                          << QStringLiteral("T3q w e r t y u i o p [ ] ")
                                          << QStringLiteral("C4a s d f g h j k l ň { } R3")
                                          << QStringLiteral("S5< w x c v b n m , . _ S4");

    return lst;
}


QStringList CKeyboardLayoutUtils::portugueseKeyboardLayout() const
{
    const QStringList lst = QStringList() << QStringLiteral("\\ 1 2 3 4 5 6 7 8 9 0 \" B3" )
                                          << QStringLiteral("T3q w e r t y u i o p + ` ")
                                          << QStringLiteral("C4a s d f g h j k l ç ~ R3")
                                          << QStringLiteral("S5< z x c v b n m , . _ S4");
    return lst;
}


QStringList CKeyboardLayoutUtils::chineseKeyboardLayout() const
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


QString CKeyboardLayoutUtils::frenchShiftMapping() const
{
    return QStringLiteral("&1é2\"3'4(5-6è7_8ç9à0)°=+<>:/;.,?^¨");
}


QString CKeyboardLayoutUtils::russianShiftMapping() const
{
    return QStringLiteral("1!2\"3№4;5%6:7?8*9(0)_-=+\\/");
}


QString CKeyboardLayoutUtils::englishShiftMapping() const
{
    return QStringLiteral("1!2@3#4$5%6^7&8*9(0)-_=+[{]};:'\",<.>/?`~");
}


QString CKeyboardLayoutUtils::spanishShiftMapping() const
{
    return QStringLiteral("1!2\"3.4$5%6&7/8(9)0=.?");
}


QString CKeyboardLayoutUtils::portugueseShiftMapping() const
{
    return QStringLiteral("\\|1!2\"3#4$5%6&7/8(9]0='?");
}


QString CKeyboardLayoutUtils::chineseShiftMapping() const
{
    QString shift = QStringLiteral("1!2@3#4$5%6^7&8*9(0)_-=+\\/");
    shift += QStringLiteral("qㄡwㄊeㄍrㄐtㄔyㄗuㄧiㄛoㄟpㄅ[{]}");
    shift += QStringLiteral("aㄇsㄋdㄎfㄑgㄕhㄘjㄨkㄜlㄠ;:,\"");
    shift += QStringLiteral("zㄈxㄌcㄏvㄒbㄖnㄙmㄩ,ㄝ.ㄆ/ㄙ");
    return shift;
}

QString CKeyboardLayoutUtils::convertDeadKey(const QString &deadKey, const QString &newChar)
{
    if (hashKeys.contains(deadKey)) {
        const QString lower = newChar.toLower();
        const bool isLower = lower == newChar;
        const QHash<QString, QString> valueDeadKey = hashKeys.value(deadKey);
        const QString convertedString = valueDeadKey.value(lower);
        if (convertedString.isEmpty()) {
            return deadKey;
        } else {
            return isLower ? convertedString : convertedString.toUpper();
        }
    } else {
        return deadKey;
    }
}

bool CKeyboardLayoutUtils::isADeadKey(const QString &key)
{
    return hashKeys.contains(key);
}
