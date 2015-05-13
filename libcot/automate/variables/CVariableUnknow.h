#ifndef CVARIABLEUNKNOW_H
#define CVARIABLEUNKNOW_H CVariableUnknow

#include "IVariable.h"

#include <qobject.h>

class CVariableUnknow : public IVariable
{
	Q_OBJECT

public:
	CVariableUnknow();
	~CVariableUnknow();


	QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;
	
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
    CUnit *getUnit() const Q_DECL_OVERRIDE;
    bool isStreamRelated()const Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    bool isMeasureRelated()const Q_DECL_OVERRIDE;
    QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
    bool isDisplay()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
    void setListOutBinds(const QList<IVariable*> &) Q_DECL_OVERRIDE;
    void setListInBinds(const QList<IVariable*> &) Q_DECL_OVERRIDE;

	QVariantMap serialise() Q_DECL_OVERRIDE;
    variableAccess getAccess()const Q_DECL_OVERRIDE;
    int getAddress()const Q_DECL_OVERRIDE;
    void setRelatedStreamName(const QString &variableName) Q_DECL_OVERRIDE;
private:

    
	QString m_label;
};

#endif // CVARIABLEUNKNOW_H
