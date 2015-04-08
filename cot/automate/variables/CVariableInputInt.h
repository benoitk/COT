#ifndef CVARIBALEINPUTINT_H
#define CVARIBALEINPUTINT_H

#include "IVariable.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"


class CVariableInputInt : public QObject, public IVariable, public IVariableInput
{
	Q_OBJECT

public:
	CVariableInputInt(QObject *parent);
    CVariableInputInt(const QMap<QString, QVariant> &mapVar);
	~CVariableInputInt();

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
	void switchToUnit(CUnit*);

private:
	IVariable* readValue();
	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_iValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	organneInputType m_organneType;
	CUnit* m_unit;
	
};

#endif // CVARIBALEINPUTINT_H
