#ifndef KEYBOARDLAYOUTUTILS_H
#define KEYBOARDLAYOUTUTILS_H

#include <QStringList>
#include <QHash>
class CKeyboardLayoutUtils
{
public:
    CKeyboardLayoutUtils();
    QStringList frenchKeyboardLayout() const;
    QStringList russianKeyboardLayout() const;
    QStringList englishKeyboardLayout() const;
    QStringList spanishKeyboardLayout() const;
    QStringList portugueseKeyboardLayout() const;
    QStringList chineseKeyboardLayout() const;

    QString frenchShiftMapping() const;
    QString russianShiftMapping() const;
    QString englishShiftMapping() const;
    QString spanishShiftMapping() const;
    QString portugueseShiftMapping() const;
    QString chineseShiftMapping() const;


    QChar convertToLower(QChar currentChar, const QString &shiftMappingString);
    QChar convertToUpper(QChar currentChar, const QString &shiftMappingString);

    QString convertDeadKey(const QString &deadKey, const QString &newChar);
    bool isADeadKey(const QString &key);
private:
    //    dead key,QHash<old character, convert caracter>
    QHash<QString, QHash<QString, QString> >hashKeys;
};

#endif // KEYBOARDLAYOUTUTILS_H
