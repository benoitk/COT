#include "CVariableMutable.h"

CVariableMutable::CVariableMutable(QObject *parent)
    : IVariable(parent)
{}

CVariableMutable::CVariableMutable(const QVariantMap &data, QObject *parent)
    : IVariable(parent)
    , m_data(data)
{}

CVariableMutable::CVariableMutable(const QVariant &data, QObject *parent)
    : IVariable(parent)
{
    if (data.type() == QVariant::Map) {
        m_data = data.toMap();
    }
    else {
        setValue(data);
    }
}

CVariableMutable::~CVariableMutable()
{}

QString CVariableMutable::toString()
{
    return m_data.value("value").toString();
}

int CVariableMutable::toInt()
{
    return m_data.value("value").toInt();
}

float CVariableMutable::toFloat()
{
    return m_data.value("value").toFloat();
}

bool CVariableMutable::toBool()
{
    return m_data.value("value").toBool();
}

QVariant CVariableMutable::toVariant()
{
    return m_data.value("value");
}



void CVariableMutable::setValue(const QVariant & value)
{
    m_data["value"] = value;
    emit signalVariableChanged();
}



CVariableMutable::Type CVariableMutable::mutableType() const
{
    return CVariableMutable::Type(m_data.value("mutableType", CVariableMutable::Undefined).toInt());
}

void CVariableMutable::setMutableType(CVariableMutable::Type mutableType)
{
    m_data["mutableType"] = mutableType;
}


QVariantMap CVariableMutable::serialise()
{
    return m_data;
}

variableType CVariableMutable::getType() const
{ return type_mutable; }

VariableOrganType CVariableMutable::getOrganType() const
{ return type_organ_none; }

void CVariableMutable::switchToUnit(CUnit *)
{}

void CVariableMutable::setAccess(variableAccess access)
{
    IVariable::setAccess(access);
}

void CVariableMutable::setToBindedValue(const QVariant &)
{}


