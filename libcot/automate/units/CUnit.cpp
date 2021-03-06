#include "CUnit.h"
#include "IConverter.h"

CUnit::CUnit(QObject *parent): QObject(parent){

}
CUnit::CUnit(const QString& name, const QString& lbl): QObject(){
    m_label = lbl;
    m_name = name;
}
CUnit::~CUnit()
{

}

QString CUnit::getLabel()const{
    return m_label;
}
QString CUnit::getName()const{
    return m_name;
}

QVariant CUnit::convert(const QString &targetKey, const QVariant &sourceValue){
    IConverter* converter = m_mapConverter.value(targetKey);
    QVariant var;
    if(converter)
        var = converter->convert(sourceValue);

    return var;
}

void CUnit::addConverter(const QString &key, IConverter* converter){
    m_mapConverter.insert(key, converter);
}
void CUnit::setConvertion(const QString &key, IConverter* converter){
    m_mapConverter.insert(key, converter);

}
QMap<QString, IConverter*> CUnit::getConverters(){
    return m_mapConverter;
}

QVariantMap CUnit::serialize(){
    QVariantMap mapSerialize;
    mapSerialize.insert(QStringLiteral("name"), m_name);
    mapSerialize.insert(tr("en_US"), m_label);
    return mapSerialize;
}
