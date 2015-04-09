#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableFloat : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableFloat(QObject *parent);
	CVariableFloat(float);
	CVariableFloat();
	~CVariableFloat();

	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(float);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
	void addBind(IVariable*);
	void setToBindedValue(QVariant);
	variableType getType()const;
	void switchToUnit(CUnit*);
	//
	void delBind(IVariable*);
	void getUnit();
	bool isStreamRelated()const;
	QString getRelatedStreamName()const;
	bool isMeasureRelated()const;
	QString getRelatedMeasureName()const;
	bool isDisplay()const;
	QLinkedList<IVariable*> getListOutBinds()const;
	QLinkedList<IVariable*> getListInBinds()const;

protected:
	float m_fValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};


#endif // CVARIABLEFLOAT_H
