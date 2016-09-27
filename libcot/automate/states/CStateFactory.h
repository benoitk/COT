#ifndef CSTATEFACTORY_H
#define CSTATEFACTORY_H

#include <QObject>"
class IState;
class CStateFactory: public QObject
{
    Q_OBJECT

public:
    static IState* build(const QVariantMap&, QObject *parent);
};


#endif // CSTATEFACTORY_H
