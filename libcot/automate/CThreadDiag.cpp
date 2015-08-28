#include "CThreadDiag.h"
#include "IVariable.h"
#include "IVariableInput.h"
#include "CAutomate.h"
#include "CDisplayConf.h"
#include "qthreadpool.h"

#include "QThread"
#include "qdebug.h"
CThreadDiag::CThreadDiag(QObject* parent): QObject(parent), QRunnable(){
    this->setAutoDelete(false);
    m_stoped = false;
//    m_timer.setInterval(1000);
}

void CThreadDiag::run(){

    m_stoped = false;
    QList<IVariable*> listVars(CAutomate::getInstance()->getDisplayConf()->getListForScreenDiagnostic());
    foreach (IVariable* var, listVars) {
        if(var->getOrganType() == type_organ_input)
            m_listDiagInputVars.append(dynamic_cast<IVariableInput*>(var));
    }
    while(!m_stoped){

        foreach(IVariableInput* var, m_listDiagInputVars){
            var->readValue();
        }

        QThread::msleep(250);
    }
}
void CThreadDiag::slotReadVariables(){

}

void CThreadDiag::slotStart(){
    QThreadPool* threadPool = QThreadPool::globalInstance();
    bool result = threadPool->tryStart(this);
    if(!result && (threadPool->maxThreadCount() ==  threadPool->activeThreadCount())){
        qDebug() << "max " << threadPool->maxThreadCount() << " current " << threadPool->activeThreadCount();
        threadPool->setMaxThreadCount(threadPool->maxThreadCount()+1);
        result = threadPool->tryStart(this);
        if(!result){
            qDebug() << "can't start thread in CThreadDiag::slotStart()";
        }
    }
}
void CThreadDiag::slotStop(){
    m_stoped = true;
}
