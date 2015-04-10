#ifndef CCYCLEFACTORY_H
#define CCYCLEFACTORY_H

#include <QObject>

class ICycle;
class IAction;
class CCycleFactory : public QObject
{
	Q_OBJECT

public:
    static ICycle* build(const QVariantMap &mapCycle,QMap<QString, IAction*> mapAction);
	

private:
	
};

#endif // CCYCLEFACTORY_H
