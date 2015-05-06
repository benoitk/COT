#ifndef CCYCLEFACTORY_H
#define CCYCLEFACTORY_H

#include <QObject>

#include "ICycle.h"

class IAction;
class CCycleFactory : public QObject
{
	Q_OBJECT

public:
    static ICycle* build(const QVariantMap &mapCycle, const QMap<QString, IAction *> &mapAction);
    static ICycle* build(eTypeCycle type);

private:
	
};

#endif // CCYCLEFACTORY_H
