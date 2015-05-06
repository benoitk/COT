#include "CVariableMutable.h"

CVariableMutable::CVariableMutable(QObject *parent)
    : QObject(parent)
{}

CVariableMutable::CVariableMutable(const QVariantMap &data, QObject *parent)
    : QObject(parent)
    , m_data(data)
{}

CVariableMutable::CVariableMutable(const QVariant &data, QObject *parent)
    : QObject(parent)
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

QVariant CVariableMutable::toVariant() const
{
    return m_data.value("value");
}

QString CVariableMutable::getLabel() const
{
    return m_data.value("label").toString();
}

QString CVariableMutable::getName() const
{
    return m_data.value("name").toString();
}

void CVariableMutable::setName(const QString &name)
{
    m_data["name"] = name;
}

void CVariableMutable::setLabel(const QString &label)
{
    m_data["label"] = label;
}

void CVariableMutable::setValue(const QVariant & value)
{
    m_data["value"] = value;
}

variableAccess CVariableMutable::getAccess() const
{
    return variableAccess(m_data.value("access", access_read_write).toInt());
}

void CVariableMutable::setAccess(variableAccess access)
{
    m_data["access"] = access;
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
{ return VariableOrganTypeNone; }

void CVariableMutable::switchToUnit(CUnit *)
{}

CUnit *CVariableMutable::getUnit() const
{ return Q_NULLPTR; }

bool CVariableMutable::isStreamRelated() const
{ return false; }

QString CVariableMutable::getRelatedStreamName() const
{ return QString(); }

bool CVariableMutable::isMeasureRelated() const
{ return false; }

QString CVariableMutable::getRelatedMeasureName() const
{ return QString(); }

void CVariableMutable::addBind(IVariable *)
{}

void CVariableMutable::delBind(IVariable *)
{}

void CVariableMutable::setToBindedValue(const QVariant &)
{}

bool CVariableMutable::isDisplay() const
{ return false; }

QList<IVariable *> CVariableMutable::getListOutBinds() const
{ return QList<IVariable *>(); }

QList<IVariable *> CVariableMutable::getListInBinds() const
{ return QList<IVariable *>(); }

int CVariableMutable::getAddress() const
{ return -1; }

