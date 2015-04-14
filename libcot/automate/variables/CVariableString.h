#ifndef CVARIABLESTRING_H
#define CVARIABLESTRING_H 

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

#include "cot_global.h"

#ifndef NOT_SHAREDLIB
class COTWIDGETS_EXPORT CVariableString : public QObject, public IVariable
#else
class CVariableString : public QObject, public IVariable
#endif
{
	Q_OBJECT

public:
	CVariableString(QObject *parent);
    CVariableString(const QString&);
	~CVariableString();

	QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;

    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(QString);
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

private:
	QString m_sValeur;
    QString m_name;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};


#endif // CVARIABLESTRING_H
