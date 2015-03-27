#ifndef CInt_H
#define CInt_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInt : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableInt(QObject *parent);
	CVariableInt(int);
	~CVariableInt();

	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(int iValeur);
	void setValue(QVariant value);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
	void addBind(IVariable*);
	void setToBindedValue(QVariant);
	variableType getType()const;
	void switchToUnit(CUnit*);

private:
	int m_iValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};

#endif // CInt_H
