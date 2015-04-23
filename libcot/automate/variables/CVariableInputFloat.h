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
    CVariableInputFloat(QObject *parent = Q_NULLPTR);
    CVariableInputFloat(const QMap<QString, QVariant> &mapVar);
	~CVariableInputFloat();

	


	
	
	
    //IVariableInput
    CModelExtensionCard* getExtensionCard()const Q_DECL_OVERRIDE;
    QString getOrganneName()const Q_DECL_OVERRIDE;
    QString getOrganneAddr()const Q_DECL_OVERRIDE;
    void setOrganne(CModelExtensionCard* ,QString) Q_DECL_OVERRIDE;
    IComObserver* getComObserver()const Q_DECL_OVERRIDE;
    IVariable* getIVariable() Q_DECL_OVERRIDE;

	//IVariable
    QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE; QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(float);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
    QString getLabel()const Q_DECL_OVERRIDE;
    void setLabel(const QString &) Q_DECL_OVERRIDE;
	//QString getName()const;
    void addBind(IVariable*) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    VariableOrganType getOrganType() const Q_DECL_OVERRIDE { return VariableOrganTypeInput; }
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
	//
    void delBind(IVariable*) Q_DECL_OVERRIDE;
    CUnit *getUnit() const Q_DECL_OVERRIDE;
    bool isStreamRelated()const Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    bool isMeasureRelated()const Q_DECL_OVERRIDE;
    QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
    bool isDisplay()const Q_DECL_OVERRIDE;
    QLinkedList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    QLinkedList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;


private:
    IVariable* readValue() Q_DECL_OVERRIDE;

	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	float m_fValeur;
    QString m_name;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;


};

#endif // CVARIABLEINPUTFLOAT_H
