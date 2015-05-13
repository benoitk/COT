#ifndef CACTIONFACTORY_H
#define CACTIONFACTORY_H

#include <QObject>

class IAction;
class CActionFactory : public QObject
{
    Q_OBJECT

public:
    static IAction* build(const QVariantMap&);

};

#endif // CACTIONFACTORY_H
