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

    static IVariablePtr buildTemporaryString(const QString& name);
    static IVariablePtr buildTemporaryString(const QString& name, const QString &label);
    static IVariablePtr buildTemporaryString(const QString& name, const QString &label, const QVariant &value);
    static IVariablePtrList buildTemporaryString(const QStringList& names);
    static void deleteTemporaryStringList(IVariablePtrList& ivars);

private:
	
};

#endif // CVARIABLEFACTORY_H
