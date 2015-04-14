#ifndef CVARIABLEUNKNOW_H
#define CVARIABLEUNKNOW_H CVariableUnknow

#include "IVariable.h"

#include <qobject.h>

class CVariableUnknow : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableUnknow();
	~CVariableUnknow();

<<<<<<< HEAD
	QString toString() Q_DECL_OVERRIDE;
	int toInt() Q_DECL_OVERRIDE;
	float toFloat() Q_DECL_OVERRIDE;
	bool toBool() Q_DECL_OVERRIDE;
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
=======
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
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
>>>>>>> 4457cb1e95a6492c345a58d64beb5bfede86aecb
private:
	QString m_label;
};

#endif // CVARIABLEUNKNOW_H
