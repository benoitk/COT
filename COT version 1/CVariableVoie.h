#ifndef CVOIE_H
#define CVOIE_H

#include "ilistvariable.h"

class CVariableVoie : public IVariable
{
	Q_OBJECT

public:
	CVariableVoie(QObject *parent);
	CVariableVoie(QObject *parent, int iNumVoie);
	~CVariableVoie();
	QString toString()const;
	int toInt()const;
	float toFloat()const;
	void setValue(int iNumVoie);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
private:
	int m_iNumVoie;
	QString m_label;
};

#endif // CVOIE_H
