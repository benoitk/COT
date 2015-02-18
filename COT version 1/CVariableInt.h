#ifndef CInt_H
#define CInt_H

#include "IVariable.h"

class CVariableInt : public IVariable
{
	Q_OBJECT

public:
	CVariableInt(QObject *parent);
	CVariableInt(int);
	~CVariableInt();

	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(int iValeur);
	void setValue(QVariant value);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;

private:
	int m_iValeur;
	QString m_label;
};

#endif // CInt_H
