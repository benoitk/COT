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
	~CUnit();
	QString getLbl()const;
	QString getName()const;
	QVariant convert(QString, QVariant);
	void addConvertion(QString, IConverter*);
	void setConvertion(QString, IConverter*);

private:
	QString m_lbl;
	QString m_name;
	QMap<QString, IConverter*> m_mapConverter;

};

#endif // CUNIT_H
