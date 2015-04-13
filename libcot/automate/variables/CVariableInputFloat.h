#ifndef CVARIABLEINPUTFLOAT_H
#define CVARIABLEINPUTFLOAT_H

#include "IVariable.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputFloat : public QObject,public IVariable, public IVariableInput
{
	Q_OBJECT

public:
	CVariableInputFloat(QObject *parent);
    CVariableInputFloat(const QMap<QString, QVariant> &mapVar);
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
	void switchToUnit(CUnit*);
	//
	void delBind(IVariable*);
	void getUnit();
	bool isStreamRelated()const;
	QString getRelatedStreamName()const;
	bool isMeasureRelated()const;
	QString getRelatedMeasureName()const;
	bool isDisplay()const;
	QLinkedList<IVariable*> getListOutBinds()const;
	QLinkedList<IVariable*> getListInBinds()const;


private:
	IVariable* readValue();

	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_fValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	organneInputType m_organneType;
	CUnit* m_unit;


};

#endif // CVARIABLEINPUTFLOAT_H
