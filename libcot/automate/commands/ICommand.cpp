#include "ICommand.h"
#include <QVariantMap>

ICommand::ICommand(const QVariantMap &mapCmd, QObject *parent) : QObject(parent)
{
    m_label = mapCmd.value(tr("en_US")).toString();
    if(m_label == "" ) m_label = tr("None given label");
    m_name = mapCmd.value(QStringLiteral("name")).toString();
    if(m_name == "") m_name =  tr("None given name");


}

QString ICommand::getName(){
    return m_name;
}

commandType ICommand::getType(){
    return m_type;
}


