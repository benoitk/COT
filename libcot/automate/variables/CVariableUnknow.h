#ifndef CVARIABLEUNKNOW_H
#define CVARIABLEUNKNOW_H CVariableUnknow

#include "IVariable.h"

#include <qobject.h>

class CVariableUnknow : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableUnknow();
	~CVariableUnknow();

	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
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
	QString m_label;
};

#endif // CVARIABLEUNKNOW_H
