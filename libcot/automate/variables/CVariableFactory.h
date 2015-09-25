#ifndef CVARIABLEFACTORY_H
#define CVARIABLEFACTORY_H

#include <QObject>

#include "IVariable.h"

class CVariableFactory
{
public:
    static IVariable* build(const QVariantMap &config);
    static IVariable* build(enumVariableType type, enumVariableOrganType organType = e_type_organ_none, const QVariant &data = QVariant());
    static IVariable* build(const QString& type, const QVariantMap &data = QVariantMap());

    static QString buildTemporaryName(const QString &baseName);
    static IVariablePtr buildTemporary(const QString& name, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr buildTemporary(const QString& name, const QString &label, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr buildTemporary(const QString& name, const QString &label, const QVariant &value, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtrList buildTemporary(const QStringList& names, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr duplicateTemporary(IVariablePtr variable);
    static void deleteVariables(IVariablePtrList& ivars);
    static void deleteVariables(QHash<QString, IVariablePtr>& ivars);
    static void deleteVariables(QMap<QString, IVariablePtr>& ivars);

    template <typename T>
    static T castedBuild(enumVariableType type, enumVariableOrganType organType = e_type_organ_none, const QVariant &data = QVariant()) {
        return static_cast<T>(build(type, organType, data));
    }
};

#endif // CVARIABLEFACTORY_H
