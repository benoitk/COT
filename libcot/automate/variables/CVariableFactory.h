#ifndef CVARIABLEFACTORY_H
#define CVARIABLEFACTORY_H

#include <QObject>
#include "IVariable.h"

class CVariableFactory : public QObject
{
	Q_OBJECT

public:
	

    static IVariable* build(const QMap<QString, QVariant> &);
    static IVariable* build(const QString&);

private:
	
};

#endif // CVARIABLEFACTORY_H
