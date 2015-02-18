#ifndef CVARIABLEBOOL_H
#define CVARIABLEBOOL_H

#include "IVariable.h"

class CVariableBool : public IVariable
{
	Q_OBJECT

public:
	CVariableBool(QObject *parent);
	CVariableBool(bool);
	~CVariableBool();

	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(bool);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
private:
	bool m_bValeur;
	QString m_label;
};
#endif // CVARIABLEBOOL_H
