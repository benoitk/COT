#ifndef CCYCLEFACTORY_H
#define CCYCLEFACTORY_H

#include <QObject>

#include "ICycle.h"

class IAction;
class CCycleFactory : public QObject
{
    Q_OBJECT

public:
    static ICycle* build(eTypeCycle type);
    static ICycle* build(const QVariantMap &mapCycle, QObject* paren);


private:

};

#endif // CCYCLEFACTORY_H
