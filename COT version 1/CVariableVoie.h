#ifndef CVOIE_H
#define CVOIE_H

#include "IVariable.h"

#include <qobject.h>

class CVariableVoie : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableVoie(QObject *parent);
	CVariableVoie(QObject *parent, int iNumVoie);
	~CVariableVoie();
	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(int iNumVoie);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	void setToBindedValue(QVariant);
	variableType getType()const;
private:
	int m_iNumVoie;
	QString m_label;
};

#endif // CVOIE_H
