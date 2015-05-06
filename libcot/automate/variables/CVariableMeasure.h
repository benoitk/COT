#ifndef CVARIABLEMEASURE_H
#define CVARIABLEMEASURE_H

#include "IVariable.h"
#include <QObject>

class ICycle;
class CVariableMeasure : public QObject, public IVariable
{
    Q_OBJECT

public:
    CVariableMeasure(QObject *parent = Q_NULLPTR);
    CVariableMeasure(const QMap<QString, QVariant> &mapVar);

    QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;
	
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(int iNumVoie);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
	QString getLabel()const;
    void setLabel(const QString &) Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
	//
	void addBind(IVariable*) Q_DECL_OVERRIDE;
    void delBind(IVariable*) Q_DECL_OVERRIDE;
    CUnit *getUnit() const Q_DECL_OVERRIDE;
    bool isStreamRelated()const Q_DECL_OVERRIDE;
    QString getRelatedStreamName()const Q_DECL_OVERRIDE;
    bool isMeasureRelated()const Q_DECL_OVERRIDE;
    QString getRelatedMeasureName()const Q_DECL_OVERRIDE;
    bool isDisplay()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
	QVariantMap serialise() Q_DECL_OVERRIDE;

    QList<IVariable*> getListVariables();  
    IVariable* getMeasureVariable();
    IVariable * getMeasureMax();
    IVariable * getMeasureMin();

    variableAccess getAccess()const Q_DECL_OVERRIDE;
    int getAddress()const Q_DECL_OVERRIDE;

private:

    int m_address;
    variableAccess m_access;
    QString m_name;
	QString m_label;
    IVariable * m_measure;
    IVariable * m_measureMax;
    IVariable * m_measureMin;

    QList<IVariable*> m_listVariables;
    
};

#endif // CVARIABLEMEASURE_H
