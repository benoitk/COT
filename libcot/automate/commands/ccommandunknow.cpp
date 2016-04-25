#include "ccommandunknow.h"

CCommandUnknow::CCommandUnknow(const QVariantMap &mapCmd, QObject *parent): ICommand(mapCmd, parent)
{

}

bool CCommandUnknow::slotRunCommand(bool arg_externalCmdOnly){
    return false;
}
void CCommandUnknow::slotReadInput(){

}
QVariantMap CCommandUnknow::serialize(){
    QVariantMap mapSerialise = ICommand::serialize();
    return mapSerialise;
}
