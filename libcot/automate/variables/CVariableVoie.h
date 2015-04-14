#ifndef CVOIE_H
#define CVOIE_H

#include "IVariable.h"

#include <qobject.h>

class CVariableVoie : public QObject, public IVariable
{
	Q_OBJECT

public:
	CVariableVoie(QObject *parent);
	CVariableVoie(QObject *parent, int iNumVoie);
	~CVariableVoie();
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(int iNumVoie);
    void setValue(QVariant) Q_DECL_OVERRIDE;
	QString getLabel()const;
    void setLabel(QString) Q_DECL_OVERRIDE;
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
	int m_iNumVoie;
	QString m_label;
};

#endif // CVOIE_H
