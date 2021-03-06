#ifndef CUNIT_H
#define CUNIT_H

#include <QObject>
#include <qmap.h>

class IConverter;
class CUnit : public QObject
{
    Q_OBJECT

public:
    CUnit(QObject *parent);
    CUnit(const QString&, const QString&);
    ~CUnit();
    QString getLabel()const;
    QString getName()const;
    QVariant convert(const QString &, const QVariant &);
    void addConverter(const QString &, IConverter*);
    void setConvertion(const QString &, IConverter*);
    QMap<QString, IConverter*> getConverters();
    QVariantMap serialize();
private:
    QString m_label;
    QString m_name;
    QMap<QString, IConverter*> m_mapConverter;

};

#endif // CUNIT_H
