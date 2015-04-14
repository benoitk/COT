#ifndef CVARIABLEFLOAT_H
#define CVARIABLEFLOAT_H CVariableFloat

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableFloat : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableFloat(QObject *parent);
	CVariableFloat(float);
	CVariableFloat();
	~CVariableFloat();

    QString toString() Q_DECL_OVERRIDE;
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

protected:
	float m_fValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};


#endif // CVARIABLEFLOAT_H
