#include "ICycle.h"
//#include "qvariant.h"
//#include "qmap.h"
//
//
//#include "CCycleAutonome.h"
//#include "CCycleIO.h"
//#include "CCycleMaintenance.h"
//#include "CCycleMesure.h"
//#include "CCyclePause.h"
//
//#include "cotautomate_debug.h"

ICycle::ICycle(QObject *parent)
    : QObject(parent)
{

}
ICycle::ICycle()
    : QObject(), m_isRunning(false)
{

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
