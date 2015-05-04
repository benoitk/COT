#ifndef CVOIE_H
#define CVOIE_H

#include "IVariable.h"

#include <qobject.h>

class ICycle;
class CVariableMeasure;
class CVariableVoie : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableVoie(QObject *parent);
    CVariableVoie(const QMap<QString, QVariant> &mapVar);
	~CVariableVoie();

	QString getName()const Q_DECL_OVERRIDE;
	void setName(const QString&)Q_DECL_OVERRIDE;
	
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(int iNumVoie);
    void setValue(const QVariant &) Q_DECL_OVERRIDE;
	QString getLabel()const Q_DECL_OVERRIDE;
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
    QLinkedList<IVariable*> getListOutBinds()const Q_DECL_OVERRIDE;
    QLinkedList<IVariable*> getListInBinds()const Q_DECL_OVERRIDE;
	QVariantMap serialise() Q_DECL_OVERRIDE;

    QList<IVariable*> getListVariables();  
    QList<IVariable*> getListMeasures();
    QList<ICycle*> getListCycles();
    IVariable* getActiveState();

private:
    QString m_name;
	QString m_label;

    IVariable* m_activeState;
    QList<IVariable*> m_listVariables;
    QList<IVariable*> m_listMeasures;
    QList<ICycle*> m_listCycles;
};

#endif // CVOIE_H
