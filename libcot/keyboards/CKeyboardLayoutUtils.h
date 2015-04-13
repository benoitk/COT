#ifndef KEYBOARDLAYOUTUTILS_H
#define KEYBOARDLAYOUTUTILS_H

#include <QStringList>

namespace CKeyboardLayoutUtils
{
    QStringList frenchKeyboardLayout();
    QStringList russianKeyboardLayout();
    QStringList englishKeyboardLayout();
    QStringList spanishKeyboardLayout();
    QStringList portugueseKeyboardLayout();
    QStringList chineseKeyboardLayout();

    QString frenchShiftMapping();
    QString russianShiftMapping();
    QString englishShiftMapping();
    QString spanishShiftMapping();
    QString portugueseShiftMapping();
    QString chineseShiftMapping();


    QChar convertToLower(QChar currentChar, const QString &shiftMappingString);
    QChar convertToUpper(QChar currentChar, const QString &shiftMappingString);
}

#endif // KEYBOARDLAYOUTUTILS_H
