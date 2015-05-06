#ifndef CVARIABLEFACTORY_H
#define CVARIABLEFACTORY_H

#include <QObject>
#include "IVariable.h"

class CVariableFactory : public QObject
{
	Q_OBJECT

public:
    static IVariable* build(const QMap<QString, QVariant> &);
    static IVariable* build(variableType type, VariableOrganType organType = VariableOrganTypeNone, const QVariant &data = QVariant());
    static IVariable* build(const QString& type, const QVariantMap &data = QVariantMap());

    static IVariablePtr buildTemporary(const QString& name, variableType type);
    static IVariablePtr buildTemporary(const QString& name, const QString &label, variableType type);
    static IVariablePtr buildTemporary(const QString& name, const QString &label, const QVariant &value, variableType type);
    static IVariablePtrList buildTemporary(const QStringList& names, variableType type);
    static void deleteVariables(IVariablePtrList& ivars);
    static void deleteVariables(QHash<QString, IVariablePtr>& ivars);
    static void deleteVariables(QMap<QString, IVariablePtr>& ivars);

    template <typename T>
    static T castedBuild(variableType type, VariableOrganType organType = VariableOrganTypeNone, const QVariant &data = QVariant()) {
        return static_cast<T>(build(type, organType, data));
    }

private:
	
};

#endif // CVARIABLEFACTORY_H
