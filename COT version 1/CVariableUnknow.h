#ifndef CVARIABLEUNKNOW_H
#define CVARIABLEUNKNOW_H CVariableUnknow

#include "IVariable.h"

class CVariableUnknow : public IVariable
{
	Q_OBJECT

public:
	CVariableUnknow();
	~CVariableUnknow();

	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;

private:
	QString m_label;
};

#endif // CVARIABLEUNKNOW_H
