#ifndef CVARIABLESTRING_H
#define CVARIABLESTRING_H 

#include "IVariable.h"

class CVariableString : public IVariable
{
	Q_OBJECT

public:
	CVariableString(QObject *parent);
	CVariableString(QString);
	~CVariableString();

	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(QString);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;

private:
	QString m_sValeur;
	QString m_label;
};


#endif // CVARIABLESTRING_H
