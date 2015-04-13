#ifndef CVARIABLEBOOL_H
#define CVARIABLEBOOL_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableBool : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableBool(QObject *parent);
	CVariableBool(bool);
	~CVariableBool();

	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(bool);
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


private:
	bool m_bValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};
#endif // CVARIABLEBOOL_H
