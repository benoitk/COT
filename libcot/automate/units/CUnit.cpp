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

QString CUnit::getLbl()const{
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
