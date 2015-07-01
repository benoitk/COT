#include "CThreadDiag.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "CAutomate.h"
#include "CDisplayConf.h"
#include "qthreadpool.h"

#include "QThread"

CThreadDiag::CThreadDiag(QObject* parent): QObject(parent), QRunnable(){
    this->setAutoDelete(false);
//    m_timer.setInterval(1000);
}

void CThreadDiag::run(){

    QList<IVariable*> listVars(CAutomate::getInstance()->getDisplayConf()->getListForScreenDiagnostic());
    foreach (IVariable* var, listVars) {
        if(var->getOrganType() == type_organ_input)
            m_listDiagInputVars.append(dynamic_cast<IVariableInput*>(var));
    }
    while(1){
        foreach(IVariableInput* var, m_listDiagInputVars){
            var->readValue();
        }
        QThread::msleep(200);
    }
}
void CThreadDiag::slotReadVariables(){

}

void CThreadDiag::slotStart(){
    QThreadPool::globalInstance()->tryStart(this);
}
void CThreadDiag::slotPause(){

}
