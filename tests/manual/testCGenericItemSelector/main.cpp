#include <QApplication>
#include <QMessageBox>
#include <QDateTime>

#include "CVariableString.h"
#include "CGenericItemSelector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IVariablePtrList variableList;
    QStringList strList;
    strList << QStringLiteral("Surgery")
            << QStringLiteral("Anaesthetics")
            << QStringLiteral("ER")
            << QStringLiteral("Wards")
            << QStringLiteral("Doctor")
            << QStringLiteral("Oxygen")
            << QStringLiteral("Blood")
            << QStringLiteral("Sweden")
            << QStringLiteral("France")
            << QStringLiteral("Germany")
            << QStringLiteral("Nurse")
            << QStringLiteral("bed")
            << QStringLiteral("recovery")
            << QStringLiteral("General medicine");


    for (int i = 0; i < strList.count(); ++i) {
        variableList.append(new CVariableString(strList.at(i)));
    }

    // lots of items
    for (int i = 0; i < 300; ++i) {
        variableList.append(new CVariableString(QString::number(i)));
    }

    // display dialog with choices as buttons
    CGenericItemSelector dialog(variableList);
    dialog.exec();

    if (dialog.result() == QDialog::Accepted) {
        IVariablePtr selectedItem = dialog.selectedItem();
        // display choosen icon
        QMessageBox msgBox;
        const QString returnText = QStringLiteral("You choose %1");
        msgBox.setText(returnText.arg(selectedItem?selectedItem->toString():QStringLiteral("nothing")));
        msgBox.exec();
    } else {
        QMessageBox msgBox;
        msgBox.setText(QStringLiteral("Cancelled"));
        msgBox.exec();
    }

    return a.exec();
}
