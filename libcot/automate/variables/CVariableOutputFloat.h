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
	QString toString() Q_DECL_OVERRIDE;
	int toInt() Q_DECL_OVERRIDE;
	float toFloat() Q_DECL_OVERRIDE;
	bool toBool() Q_DECL_OVERRIDE;
	void setValue(float);
	void setValue(QVariant) Q_DECL_OVERRIDE;
	QString getLabel()const Q_DECL_OVERRIDE;
	void setLabel(QString) Q_DECL_OVERRIDE;
	QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;
	void addBind(IVariable*) Q_DECL_OVERRIDE;
	void setToBindedValue(QVariant) Q_DECL_OVERRIDE;
	variableType getType()const Q_DECL_OVERRIDE;
	void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
	//
	void delBind(IVariable*) Q_DECL_OVERRIDE;
	void getUnit() Q_DECL_OVERRIDE;
	bool isStreamRelated()const Q_DECL_OVERRIDE;
	QString getRelatedStreamName()const Q_DECL_OVERRIDE;
	bool isMeasureRelated()const Q_DECL_OVERRIDE;
	QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
	bool isDisplay()const Q_DECL_OVERRIDE;
	QLinkedList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
	QLinkedList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
private:
	void writeValue();
	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_fValeur;
    QString m_name;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	organneOutputType m_organneType;
	CUnit* m_unit;
	
};

#endif // CVARIABLEOUTPUTFLOAT_H
