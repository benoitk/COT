#include "ICycle.h"
#include "CStep.h"
#include "CAutomate.h"
#include "CScheduler.h"
#include "cotautomate_debug.h"
#include "qthread.h"

ICycle::ICycle(CScheduler *parent)
    : QObject(parent)
    , m_stepStop(Q_NULLPTR)
    , m_editInProgress(false)
    , m_mutex(QMutex::Recursive)
    , m_scheduler(parent)
{

}
//ICycle::ICycle()
//    : QObject()
//    , m_isRunning(false)
//    , m_stepStop(Q_NULLPTR)
//    , m_editInProgress(false)
//    , m_mutex(QMutex::Recursive)
//{

//}
ICycle::ICycle(const QVariantMap &mapCycle, CScheduler *parent)
    : QObject(parent)
    , m_isRunning(false)
    , m_stepStop(Q_NULLPTR)
    , m_editInProgress(false)
    , m_mutex(QMutex::Recursive)
    ,m_scheduler(parent)
{

    if(mapCycle.contains(QStringLiteral("name")))
        m_name = mapCycle[QStringLiteral("name")].toString();
    else
        m_name = QStringLiteral("Cycle not named");
    m_label = mapCycle[tr("en_US")].toString();

    if(mapCycle.contains(QStringLiteral("steps"))){
        const QVariantList listSteps = mapCycle[QStringLiteral("steps")].toList();
        foreach(const QVariant &varStep, listSteps){
            const QVariantMap mapStep = varStep.toMap();
            CStep* step = new CStep(this, mapStep);
            m_listSteps.append(step);
        }
        if(!m_listSteps.isEmpty() &&  m_listSteps.first()->getNumStep() != 0){
            CStep* step = new CStep(this);
            m_listSteps.prepend(step);
        }
    }
    if(mapCycle.contains(QStringLiteral("step_stop"))){
        const QVariantMap mapStepStop = mapCycle[QStringLiteral("step_stop")].toMap();
        m_stepStop = new CStep(this, mapStepStop);
        m_itListStepsPasEnCours == m_listSteps.end();
    }
    else
        m_stepStop = new CStep(this, QVariantMap());
}
CScheduler* ICycle::getScheduler(){
    return m_scheduler;
}

void ICycle::abortCycle(){
    QThread* currentThread = QThread::currentThread();
    if(m_mapTimerSchedulerStep.contains(currentThread) && m_mapTimerInfoNumStep.contains(currentThread)){
        m_mapTimerSchedulerStep.value(currentThread)->stop();
        m_mapTimerInfoNumStep.value(currentThread)->stop();
    }
    else
        qDebug() << "TIMER NON CREE DANS CE CYCLE , cycle :" << this->getName() ;

    foreach(CStep* step, m_listSteps){
        step->abortStep();
    }

    if(m_itListStepsPasEnCours != m_listSteps.end())
        m_itListStepsPasEnCours = m_listSteps.end();
}

bool ICycle::isRunning()const {return m_isRunning;}
bool ICycle::isPaused()const{ return m_isPaused;}

bool ICycle::isStreamRelated() const
{
    return !getRelatedStreamName().isEmpty();
}

CStep *ICycle::getStep(int index) const
{
    return getListSteps().at(index);
}

QString ICycle::typeToString(enumTypeCycle type)
{
    switch (type) {
        case e_cycle_all:
            return tr("All");

        case e_cycle_measure:
            return tr("Measure");

        case e_cycle_autonome:
            return tr("Autonome");

        case e_cycle_maintenance:
            return tr("Maintenance");

        case e_cycle_pause:
            return tr("Pause");

        case e_cycle_invalid:
            return tr("Invalid");
    }

    return QStringLiteral("**unhandled cycle type**");
}

void ICycle::startEditing(){
    if(!m_editInProgress){
        m_savedListSteps = m_listSteps;
        m_editInProgress = true;
    }
}
void ICycle::slotValidateEditing(){
    if(m_editInProgress)
        clearSavedListSteps();
    m_editInProgress = false;
}
 void ICycle::slotCancelEditing(){
     if(m_editInProgress)
         m_listSteps.swap(m_savedListSteps);
     clearSavedListSteps();
     m_editInProgress = false;
 }
void ICycle::clearSavedListSteps(){
    foreach(CStep* step, m_savedListSteps){
        if(!m_listSteps.contains(step)){
            delete step;
        }
    }
    m_savedListSteps.clear();
}

bool ICycle::swapStep(float from, float to){
    startEditing();

    int indexFrom = m_listSteps.count();
    int indexTo = m_listSteps.count();


    for(int  i = 0; i < m_listSteps.count() && indexFrom == m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() == from ){
            indexFrom = i;
            m_listSteps.value(i)->setNumStep(to);

        }
    }
    if(indexFrom == m_listSteps.count()) return false; //le pas de départ n'éxiste pas


    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.value(i)->getNumStep() == to ){
            indexTo = i;
            m_listSteps.value(i)->setNumStep(from);

        }
    }
    if(indexTo == m_listSteps.count()) return false; //le pas d'arrivé n'éxiste pas

    m_listSteps.swap(indexFrom, indexTo);

    return true;
}

bool ICycle::copySteps(float from, float length, float to){
    startEditing();

    int indexFrom = m_listSteps.count();
    int indexTo = m_listSteps.count();
    QList<CStep*> listTemp;

    for(int  i = 0; i < m_listSteps.count() && m_listSteps.at(i)->getNumStep() <= from+length; ++i){
        if(!listTemp.isEmpty()){
            listTemp.append(m_listSteps.at(i));
        }else if(m_listSteps.at(i)->getNumStep() == from ){
            listTemp.append(m_listSteps.at(i));
        }
    }
    if(listTemp.isEmpty()) return false; //pas de pas dans l'intervale

    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.value(i)->getNumStep() >= to && m_listSteps.value(i)->getNumStep() <= to+length){
            indexTo = i; //déjà un pas présent, on le met à la place
            if(this->moveSteps(m_listSteps.value(i)->getNumStep()
                               , length-m_listSteps.value(i)->getNumStep()
                               , to+length+0.1)); //décale les pas suivants
        }else if(m_listSteps.value(i)->getNumStep() > to ){
            indexTo = i;
        }
    }

    if(indexTo == m_listSteps.count()) m_listSteps.append(listTemp);
    else{
        for(int i = listTemp.count()-1; i >= 0; --i){
            m_listSteps.insert(indexTo, listTemp.at(i));
        }
    }
    return true;
}

bool ICycle::copyStep(float from, float to){
    startEditing();

    int indexFrom = m_listSteps.count();
    int indexTo = m_listSteps.count();

    bool indexFound = false;
    for(int  i = 0; i < m_listSteps.count() && indexFrom == m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() == from ){
            indexFrom = i;
            m_listSteps.value(i)->setNumStep(to);
            indexFound = true;
        }
    }
    if(!indexFound) return false; //le pas de départ n'éxiste pas

    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.value(i)->getNumStep() == to ){
            indexTo = i; //déjà un pas présent, on le met à la place
            if(this->moveStep(to, to+0.1)); //décale le pas suivant
        }else if(m_listSteps.value(i)->getNumStep() > to ){
            indexTo = i;
        }
    }

    if(indexTo == m_listSteps.count()) m_listSteps.append(m_listSteps.at(indexFrom));
    else m_listSteps.insert(indexTo, m_listSteps.at(indexFrom));

    return true;
}
void ICycle::shiftAllSteps(float arg_from, float arg_shifting, int arg_index){

    for(int i= arg_index; i<m_listSteps.count(); ++i){
        CStep* step = m_listSteps.value(i);
        if(step->getNumStep() > arg_from){
            step->setNumStep(step->getNumStep() + arg_shifting);
        }
    }

}

bool ICycle::moveSteps(float from, float length, float to){
    startEditing();

    int indexFrom = m_listSteps.count();

    QList<CStep*> listTemp;

    for(int  i = 0; i < m_listSteps.count() && m_listSteps.at(i)->getNumStep() < from+length; ++i){
        if(!listTemp.isEmpty()){
            listTemp.append(m_listSteps.takeAt(i--));
        }else if(m_listSteps.at(i)->getNumStep() == from ){
            listTemp.append(m_listSteps.takeAt(i--));
        }
    }
    if(listTemp.isEmpty()) return false; //pas de pas dans l'intervale

    int indexTo = m_listSteps.count();
    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() >= to && m_listSteps.value(i)->getNumStep() <= to+length){
            indexTo = i; //déjà un pas présent, on le met à la place et on décale le reste d'un bloc
            shiftAllSteps(m_listSteps.value(i)->getNumStep(), length);
        }else if(m_listSteps.at(i)->getNumStep() > to ){
            indexTo = i;
        }
    }

    if(indexTo == m_listSteps.count()) m_listSteps.append(listTemp);
    else{
        for(int i = listTemp.count()-1; i >= 0; --i){
            m_listSteps.insert(indexTo, listTemp.at(i));
        }
    }
    return true;
}

//Les pas from doitt exister.
bool ICycle::moveStep(float from, float to){
    startEditing();

    int indexFrom = m_listSteps.count();
    int indexTo = m_listSteps.count();

    bool indexFound = false;
    for(int  i = 0; i < m_listSteps.count() && indexFrom == m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() == from ){
            indexFrom = i;
            m_listSteps.value(i)->setNumStep(to);
            indexFound = true;
        }
    }
    if(!indexFound) return false; //le pas de départ n'éxiste pas

    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.value(i)->getNumStep() == to ){
            indexTo = i; //déjà un pas présent, on le met à la place
            shiftAllSteps(m_listSteps.at(i)->getNumStep(), 1);
        }else if(m_listSteps.value(i)->getNumStep() > to ){
            indexTo = i;
        }
    }

    if(indexTo == m_listSteps.count()) m_listSteps.append(m_listSteps.takeAt(indexFrom));
    else m_listSteps.move(indexFrom, indexTo);

    return true;
}

bool ICycle::deleteSteps(float from, float length){
    startEditing();

    QList<CStep*>::iterator it;
    bool someStepErased = false;

    for(int i =0; i < m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() >= from && m_listSteps.at(i)->getNumStep() <= (from+length) ){
            delete m_listSteps.takeAt(i);
            someStepErased =  true;
        }else if(m_listSteps.at(i)->getNumStep() > (from+length)) break;
    }
    return someStepErased;
}

bool ICycle::deleteStep(float at){
    startEditing();

    QList<CStep*>::iterator it;
    CStep* step = Q_NULLPTR;
    for(int i =0; i < m_listSteps.count(); ++i){
        if(m_listSteps.at(i)->getNumStep() == at){
            delete m_listSteps.takeAt(i);
            return true;
        }
    }
    return false;
}

CStep* ICycle::addStep(float pos, const QString& lbl){
    startEditing();

    //debug
    foreach(CStep* s, m_listSteps){
        qCDebug(COTAUTOMATE_LOG)  << "step name : " << s->getLabel() << " num : " << s->getNumStep();
    }

    //fin debug
    QList<CStep*>::iterator it;
    CStep* newStep = Q_NULLPTR;
    bool stepInserted= false;

    for(it = m_listSteps.begin(); it != m_listSteps.end() && !stepInserted; ++it){
        if((*it)->getNumStep() == pos) return Q_NULLPTR;
        if((*it)->getNumStep() > pos && it == m_listSteps.begin()){
            m_listSteps.prepend(newStep = new CStep(this, QVariantMap()));
            stepInserted = true;
        }else if( (*it)->getNumStep() > pos && it != m_listSteps.begin()){
            --it;
            m_listSteps.insert(it, newStep = new CStep(this, QVariantMap()));
            stepInserted = true;
        }
    }
    if(!stepInserted){
        m_listSteps.append(newStep = new CStep(this, QVariantMap()));
    }

    if(newStep){
        newStep->setNumStep(pos);
        newStep->setLabel(lbl);
    }

    foreach(CStep* s, m_listSteps){
        qCDebug(COTAUTOMATE_LOG)  << "step name : " << s->getLabel() << " num : " << s->getNumStep();
    }
    return newStep;
}

QVariantMap ICycle::serialize(){

    QVariantMap mapSerialise;
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("en_US"), m_label);


    QVariantList listSteps;
    foreach(CStep* step, m_listSteps){
        listSteps.append(step->serialize());
    }
    mapSerialise.insert(QStringLiteral("steps"), listSteps);
    mapSerialise.insert(QStringLiteral("step_stop"), m_stepStop->serialize());

    return mapSerialise;
}

QString ICycle::getRelatedStreamName()const{

    return "méthode à supprimer";//m_streamName;
}
CVariableStream* ICycle::getRelatedStream()const{
    return Q_NULLPTR; //méthode à supprimer
}
void ICycle::setRelatedStreamName(const QString &name)
{
    //m_streamName = name;
}
QList<CStep*> ICycle::getListSteps()const{
    return m_listSteps;
}
CStep* ICycle::getStepStop()const{
    return m_stepStop;
}

void ICycle::setListSteps(const QList<CStep *> &steps, CStep *stopStep)
{
    qDeleteAll(m_listSteps);
    delete m_stepStop;
    m_listSteps = steps;
    m_stepStop = stopStep;
}

int ICycle::getCurrentStepIndex() const
{
    return -1;
}
QString ICycle::getLabel()const{ return m_label;}
void ICycle::setLbl(const QString &lbl){ m_label = lbl;}

void ICycle::addAction(float arg_step, IAction* action){
    QMutexLocker lock(&m_mutex);

    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        if((*itListStep)->getNumStep() == arg_step){
            (*itListStep)->addAction(action);
            itListStep = m_listSteps.end();
        }
    }
}
//enlève toutes les référence à arg_action
void ICycle::removeAction(IAction* arg_action){
    QMutexLocker lock(&m_mutex);

    QList<CStep*>::iterator itListStep;
    for(itListStep=m_listSteps.begin(); itListStep != m_listSteps.end(); ++itListStep){
        (*itListStep)->removeAction(arg_action);
    }
}



QString ICycle::getName()const{
    return m_name;

}
void ICycle::setName(const QString &name){
    m_name = name;

}

void ICycle::updateCycleInfosStep(float arg_numStep, QString arg_info){
    QMutexLocker lock(&m_mutex);
    m_numStepInfo = arg_numStep;
    emit m_scheduler->getAutomate()->signalUpdateCurrentStep(arg_numStep, arg_info);
}
void ICycle::slotUpdateCycleInfosNumStep(){
    if(*m_itListStepsPasEnCours && (*m_itListStepsPasEnCours)->getNumStep() > m_numStepInfo)
    {
        QMutexLocker lock(&m_mutex);
        m_numStepInfo+=0.1f;

        emit m_scheduler->getAutomate()->signalUpdateNumStep(m_numStepInfo);
    }
}

void ICycle::updateCycleInfosAction(QString arg_info){
    QMutexLocker lock(&m_mutex);
    emit m_scheduler->getAutomate()->signalUpdateCurrentAction(arg_info);
}
void ICycle::updateCycleInfosCountStep(){
    QMutexLocker lock(&m_mutex);
    emit m_scheduler->getAutomate()->signalUpdateCountStep(m_listSteps.last()->getNumStep());
}
