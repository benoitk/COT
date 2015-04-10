#include "localcombobox.h"
#include <QLocale>
LocalComboBox::LocalComboBox(QWidget *parent)
    : QComboBox(parent)
{
    initializeLocale();
    connect(this, SIGNAL(activated(int)), this, SLOT(slotLocalActivated(int)));
}

LocalComboBox::~LocalComboBox()
{

}

void LocalComboBox::initializeLocale()
{
    addItem(QStringLiteral("French"), QLocale::French);
    addItem(QStringLiteral("Russian"), QLocale::Russian);
    addItem(QStringLiteral("English"), QLocale::English);
    addItem(QStringLiteral("Spanish"), QLocale::Spanish);
    addItem(QStringLiteral("Portuguese"), QLocale::Portuguese);
    addItem(QStringLiteral("Chinese"), QLocale::Chinese);
}

void LocalComboBox::slotLocalActivated(int)
{
    Q_EMIT localeSelected(currentData().value<QLocale::Language>());
}
