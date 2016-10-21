#ifndef CCYCLEFACTORY_H
#define CCYCLEFACTORY_H

#include <QObject>

#include "ICycle.h"

class IAction;
class CCycleFactory : public QObject
{
    Q_OBJECT

public:
    static ICycle* build(enumTypeCycle type);
    static ICycle* build(const QVariantMap &mapCycle, CScheduler* paren);


private:

};

#endif // CCYCLEFACTORY_H
