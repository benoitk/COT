#ifndef CVARIABLEOUTPUTFLOAT_H
#define CVARIABLEOUTPUTFLOAT_H

#include "IVariable.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputFloat : public QObject, public IVariable, public IVariableOutput
{
	Q_OBJECT

public:
	CVariableOutputFloat(QObject *parent);
    CVariableOutputFloat(const QMap<QString, QVariant> &mapVar);
	~CVariableOutputFloat();

//IVariableOutput
	CModelExtensionCard* getExtensionCard()const;
	QString getOrganneName()const;
	QString getOrganneAddr()const;
	void setOrganne(CModelExtensionCard* ,QString);
	organneOutputType getTypeOrganne()const;
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
	void writeValue();
	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_fValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	organneOutputType m_organneType;
	CUnit* m_unit;
	
};

#endif // CVARIABLEOUTPUTFLOAT_H
