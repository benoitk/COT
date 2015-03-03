#ifndef CVARIABLESTRING_H
#define CVARIABLESTRING_H 

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableString : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableString(QObject *parent);
	CVariableString(QString);
	~CVariableString();

	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(QString);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
	void addBind(IVariable*);
	void setToBindedValue(QVariant);
	variableType getType()const;

private:
	QString m_sValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
};


#endif // CVARIABLESTRING_H
