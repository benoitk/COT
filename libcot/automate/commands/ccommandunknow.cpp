#include "ccommandunknow.h"

CCommandUnknow::CCommandUnknow(const QVariantMap &mapCmd, QObject *parent): ICommand(mapCmd, parent)
{

}

bool CCommandUnknow::slotRunCommand(IVariable*){
    return false;
}
void CCommandUnknow::slotReadInput(){

}
QVariantMap CCommandUnknow::serialize(){
    QVariantMap mapSerialise = ICommand::serialize();
    return mapSerialise;
}
