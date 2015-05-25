#ifndef CACTIONFACTORY_H
#define CACTIONFACTORY_H

#include "IAction.h"
#include <QObject>

class CActionFactory : public QObject
{
    Q_OBJECT

public:
    static IAction* build(const QVariantMap&);
    static IAction* build(actionType type);
};

#endif // CACTIONFACTORY_H
