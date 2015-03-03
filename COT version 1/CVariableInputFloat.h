#ifndef CVARIABLEINPUTFLOAT_H
#define CVARIABLEINPUTFLOAT_H

#include "Ivariable.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputFloat : public QObject,public IVariable, public IVariableInput
{
	Q_OBJECT

public:
	CVariableInputFloat(QObject *parent);
	CVariableInputFloat(QMap<QString, QVariant> mapVar);
	~CVariableInputFloat();

	//IVariableInput
	CModelExtensionCard* getExtensionCard()const;
	QString getOrganneName()const;
	QString getOrganneAddr()const;
	void setOrganne(CModelExtensionCard* ,QString);
	organneInputType getTypeOrganne()const;
	IComObserver* getComObserver()const;
	IVariable* getIVariable();

	//IVariable
	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(float);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
	void addBind(IVariable*);
	void setToBindedValue(QVariant);
	variableType getType()const;



private:
	IVariable* readValue();

	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_fValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	organneInputType m_organneType;


};

#endif // CVARIABLEINPUTFLOAT_H
