#ifndef CVARIABLEBOOL_H
#define CVARIABLEBOOL_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableBool : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableBool(QObject *parent);
	CVariableBool(bool);
	~CVariableBool();

	QString toString()Q_DECL_OVERRIDE;
	int toInt()Q_DECL_OVERRIDE;
	float toFloat()Q_DECL_OVERRIDE;
	bool toBool()Q_DECL_OVERRIDE;
	void setValue(bool);
	void setValue(QVariant)Q_DECL_OVERRIDE;
	QString getLabel()const Q_DECL_OVERRIDE;
	void setLabel(QString)Q_DECL_OVERRIDE;
	QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;
	void addBind(IVariable*)Q_DECL_OVERRIDE;
	void setToBindedValue(QVariant)Q_DECL_OVERRIDE;
	variableType getType()const Q_DECL_OVERRIDE;
	void switchToUnit(CUnit*)Q_DECL_OVERRIDE;
	//
	void delBind(IVariable*)Q_DECL_OVERRIDE;
	void getUnit();
	bool isStreamRelated()const Q_DECL_OVERRIDE;
	QString getRelatedStreamName()const Q_DECL_OVERRIDE;
	bool isMeasureRelated()const Q_DECL_OVERRIDE;
	QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
	bool isDisplay()const Q_DECL_OVERRIDE;
	QLinkedList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE; 
	QLinkedList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;


private:
	bool m_bValeur;
    QString m_name;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};
#endif // CVARIABLEBOOL_H
