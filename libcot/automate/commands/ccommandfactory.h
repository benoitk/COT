#ifndef CCOMMANDFACTORY_H
#define CCOMMANDFACTORY_H


#include "ICommand.h"
#include <QObject>

class CCommandFactory: public QObject
{
    Q_OBJECT

public:
    static ICommand* build(const QVariantMap&, QObject *parent);
};

#endif // CCOMMANDFACTORY_H
