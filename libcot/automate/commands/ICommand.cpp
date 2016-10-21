#include "ICommand.h"
#include "CAutomate.h"
#include <QVariantMap>

ICommand::ICommand(const QVariantMap &mapCmd, CAutomate *parent) : QObject(parent), m_automate(parent)
{
    m_label = mapCmd.value(tr("en_US")).toString();
    if(m_label == "" ) m_label = tr("None given label");
    m_name = mapCmd.value(QStringLiteral("name")).toString();
    if(m_name == "") m_name =  tr("None given name");


}
ICommand::~ICommand(){

}

QString ICommand::getName(){
    return m_name;
}

enumCommandType ICommand::getType(){
    return m_type;
}


QVariantMap ICommand::serialize(){
    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("en_US"), m_label);


    return mapSerialise;
}
