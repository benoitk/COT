#ifndef CVARIABLEINPUTBOOL_H
#define CVARIABLEINPUTBOOL_H

#include "IVariableInput.h"
#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputBool : public QObject, public IVariable, public IVariableInput
{
	Q_OBJECT

public:
	CVariableInputBool(QObject *parent);
	CVariableInputBool(QMap<QString, QVariant> mapVar);
	~CVariableInputBool();

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

	bool m_bValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	
	CUnit* m_unit;
	organneInputType m_organneType;
};

#endif // CVARIABLEINPUTBOOL_H
