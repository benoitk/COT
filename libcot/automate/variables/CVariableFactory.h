#ifndef CVARIABLEFACTORY_H
#define CVARIABLEFACTORY_H

#include <QObject>

#include "IVariable.h"

class CVariableFactory
{
public:
    static IVariable* build(CAutomate* arg_automate, QObject* parent, const QVariantMap &config);
    static IVariable* build(CAutomate* arg_automate, QObject* parent, enumVariableType type, enumVariableOrganType organType = e_type_organ_none, const QVariant &data = QVariant());
    static IVariable* build(CAutomate* arg_automate, QObject* parent, const QString& type, const QVariantMap &data = QVariantMap());

    static QString buildTemporaryName(const QString &baseName);
    static IVariablePtr buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, const QString &label, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr buildTemporary(CAutomate* arg_automate, QObject *parent, const QString& name, const QString &label, const QVariant &value, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtrList buildTemporary(CAutomate* arg_automate, QObject *parent, const QStringList& names, enumVariableType type, enumVariableOrganType organType = e_type_organ_none);
    static IVariablePtr duplicateTemporary(CAutomate* arg_automate, QObject *parent, IVariablePtr variable);
    static void deleteVariables(IVariablePtrList& ivars);
    static void deleteVariables(QHash<QString, IVariablePtr>& ivars);
    static void deleteVariables(QMap<QString, IVariablePtr>& ivars);

    template <typename T>
    static T castedBuild(CAutomate* arg_automate, QObject *parent, enumVariableType type, enumVariableOrganType organType = e_type_organ_none, const QVariant &data = QVariant()) {
        return static_cast<T>(build(arg_automate, parent, type, organType, data));
    }
};

#endif // CVARIABLEFACTORY_H
