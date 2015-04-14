#ifndef CInt_H
#define CInt_H

#include "IVariable.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInt : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableInt(QObject *parent);
	CVariableInt(int);
	~CVariableInt();

<<<<<<< HEAD
	QString toString() Q_DECL_OVERRIDE;
	int toInt() Q_DECL_OVERRIDE;
	float toFloat() Q_DECL_OVERRIDE;
	bool toBool() Q_DECL_OVERRIDE;
	void setValue(int iValeur);
	void setValue(QVariant value) Q_DECL_OVERRIDE;
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
=======
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(int iValeur);
    void setValue(const QVariant & value) Q_DECL_OVERRIDE;
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
>>>>>>> 4457cb1e95a6492c345a58d64beb5bfede86aecb
private:
	int m_iValeur;
    QString m_name;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	CUnit* m_unit;
};

#endif // CInt_H
