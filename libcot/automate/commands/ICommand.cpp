#include "ICommand.h"

ICommand::ICommand(QObject *parent) : QObject(parent)
{


}

QString ICommand::getName(){
    return m_name;
}

commandType ICommand::getType(){
    return m_type;
}


