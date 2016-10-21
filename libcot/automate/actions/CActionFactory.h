#ifndef CACTIONFACTORY_H
#define CACTIONFACTORY_H

#include "IAction.h"
#include <QObject>

class CAutomate;
class CActionFactory : public QObject
{
    Q_OBJECT

public:
    static IAction* build(const QVariantMap&, CAutomate *parent);
    static IAction* build(actionType type,  CAutomate *parent);
};

#endif // CACTIONFACTORY_H
