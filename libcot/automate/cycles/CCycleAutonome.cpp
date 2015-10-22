#include "CCycleAutonome.h"
#include "CStep.h"
#include "cotautomate_debug.h"
#include "CVariableStream.h"
#include "CAutomate.h"
CCycleAutonome::CCycleAutonome(QObject *parent)
    :CCycleMesure(parent) {}

CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap, QObject *parent)
    :CCycleMesure(variantMap, parent){}

CCycleAutonome::CCycleAutonome(const QVariantMap &variantMap, const QMap<QString, IAction *> &actionMap, QObject *parent)
    :CCycleMesure(variantMap, parent){}

CCycleAutonome::~CCycleAutonome(){
    delete m_stepStop;
    foreach (CStep* step, m_listSteps) {
        delete step;
    }
}

QString CCycleAutonome::getRelatedStreamName()const{
    return CCycleMesure::getRelatedStreamName();
}
CVariableStream* CCycleAutonome::getRelatedStream()const{
    return CAutomate::getInstance()->getStream(CCycleMesure::getRelatedStreamName());
}
QVariantMap CCycleAutonome::serialize(){
    QVariantMap mapSerialise = ICycle::serialize();

    mapSerialise.insert(QStringLiteral("type"), QStringLiteral("autonome"));

    return mapSerialise;
}
void CCycleAutonome::setRelatedStreamName(const QString &name)
{
    CCycleMesure::setRelatedStreamName(name);
}
QList<CStep*> CCycleAutonome::getListSteps()const{
    return m_listSteps;
}
CStep* CCycleAutonome::getStepStop()const{
    return m_stepStop;
}

void CCycleAutonome::setListSteps(const QList<CStep *> &steps, CStep *stopStep)
{
    qDeleteAll(m_listSteps);
    delete m_stepStop;
    m_listSteps = steps;
    m_stepStop = stopStep;
}

int CCycleAutonome::getCurrentStepIndex() const
{
    return -1;
}
void CCycleAutonome::updateCycleInfosStep(float arg_numStep, QString arg_info){}
void CCycleAutonome::updateCycleInfosAction(QString arg_info){}
void CCycleAutonome::updateCycleInfosCountStep() {}
void CCycleAutonome::slotUpdateCycleInfosNumStep() {}
