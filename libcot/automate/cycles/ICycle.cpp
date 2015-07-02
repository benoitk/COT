#include "ICycle.h"

#include "CStep.h"
//#include "cotautomate_debug.h"

ICycle::ICycle(QObject *parent)
    : QObject(parent), m_stepStop(Q_NULLPTR), m_mutex(QMutex::Recursive)
{

}
ICycle::ICycle()
    : QObject(), m_isRunning(false), m_stepStop(Q_NULLPTR), m_mutex(QMutex::Recursive)
{

}
ICycle::ICycle(const QVariantMap &mapCycle, QObject *parent)
    : QObject(parent), m_isRunning(false), m_stepStop(Q_NULLPTR), m_mutex(QMutex::Recursive){
    if(mapCycle.contains(QStringLiteral("name")))
        m_name = mapCycle[QStringLiteral("name")].toString();
    else
        m_name = QStringLiteral("Cycle not named");
    m_label = mapCycle[tr("fr_FR")].toString();

    const QVariantList listSteps = mapCycle[QStringLiteral("steps")].toList();
    foreach(const QVariant &varStep, listSteps){
        const QVariantMap mapStep = varStep.toMap();
        CStep* step = new CStep(this, mapStep);
        m_listSteps.append(step);
    }
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

QString ICycle::typeToString(eTypeCycle type)
{
    switch (type) {
        case CYCLE_ALL:
            return tr("All");

        case CYCLE_MESURE:
            return tr("Measure");

        case CYCLE_AUTONOME:
            return tr("Autonome");

        case CYCLE_MAINTENANCE:
            return tr("Maintenance");

        case CYCLE_PAUSE:
            return tr("Pause");

        case CYCLE_INVALID:
            return tr("Invalid");
    }

    return QStringLiteral("**unhandled cycle type**");
}

bool ICycle::swapStep(float from, float to){
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
    if(indexFrom == m_listSteps.count()) return false; //le pas de départ n'éxiste pas

    indexFound = false;
    for(int  i = 0; i < m_listSteps.count() && indexTo == m_listSteps.count(); ++i){
        if(m_listSteps.value(i)->getNumStep() == to ){
            indexTo = i;
            m_listSteps.value(i)->setNumStep(from);
            indexFound = true;
        }
    }
    if(indexTo == m_listSteps.count()) return false; //le pas d'arrivé n'éxiste pas

    m_listSteps.swap(indexFrom, indexTo);

    return true;
}

bool ICycle::copySteps(float from, float length, float to){
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

bool ICycle::moveSteps(float from, float length, float to){
    int indexFrom = m_listSteps.count();
    int indexTo = m_listSteps.count();
    QList<CStep*> listTemp;

    for(int  i = 0; i < m_listSteps.count() && m_listSteps.at(i)->getNumStep() <= from+length; ++i){
        if(!listTemp.isEmpty()){
            listTemp.append(m_listSteps.takeAt(i));
        }else if(m_listSteps.at(i)->getNumStep() == from ){
            listTemp.append(m_listSteps.takeAt(i));
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

//Les pas from doitt exister.
bool ICycle::moveStep(float from, float to){
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

    if(indexTo == m_listSteps.count()) m_listSteps.append(m_listSteps.takeAt(indexFrom));
    else m_listSteps.move(indexFrom, indexTo);

    return true;
}

bool ICycle::deleteSteps(float from, float length){
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
    return newStep;
}

QVariantMap ICycle::serialise(){

    QVariantMap mapSerialise = ICycle::serialise();
    mapSerialise.insert(QStringLiteral("name"), m_name);
    mapSerialise.insert(tr("fr_FR"), m_label);


    QVariantList listSteps;
    foreach(CStep* step, m_listSteps){
        listSteps.append(step->serialise());
    }
    mapSerialise.insert(QStringLiteral("steps"), listSteps);

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
