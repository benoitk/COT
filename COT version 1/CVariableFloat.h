#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

class CVariableFloat : public IVariable
{
	Q_OBJECT

public:
	CVariableFloat(QObject *parent);
	CVariableFloat(float);
	~CVariableFloat();

	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(float);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;

private:
	float m_fValeur;
	QString m_label;
};


#endif // CVARIABLEFLOAT_H
