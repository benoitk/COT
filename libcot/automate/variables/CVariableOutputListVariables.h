﻿#ifndef CVARIABLEOUTPUTLISTVARIABLES_H
#define CVARIABLEOUTPUTLISTVARIABLES_H

#include "IVariable.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlist.h"

class CVariableOutputListVariables : public IVariable, public IVariableOutput
{
    Q_OBJECT

public:
    CVariableOutputListVariables(QObject *parent = Q_NULLPTR);
    CVariableOutputListVariables(const QMap<QString, QVariant> &mapVar);
    ~CVariableOutputListVariables();

    //IVariableOutput
    CModelExtensionCard* getExtensionCard()const Q_DECL_OVERRIDE;
    QString getOrganneName()const Q_DECL_OVERRIDE;
    QString getOrganneAddr()const Q_DECL_OVERRIDE;
    void setOrganne(CModelExtensionCard* , const QString &) Q_DECL_OVERRIDE;
    IComObserver* getComObserver()const Q_DECL_OVERRIDE;
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    QString getName()const Q_DECL_OVERRIDE;
    void setName(const QString&)Q_DECL_OVERRIDE;

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
    VariableOrganType getOrganType() const Q_DECL_OVERRIDE { return VariableOrganTypeOutput; }
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

    IVariable* getVariable(const QString&);
    void addVaraiable(IVariable*);
    void setRelatedStreamName(const QString &variableName) Q_DECL_OVERRIDE;
private:

    int m_address;
    variableAccess m_access;
    void writeValue();
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;

    QString m_name;
    QString m_label;
        QList<IVariable*> m_listBinds;
    CUnit* m_unit;

    QList<IVariable*> m_listVariables;


    void setAccess(variableAccess access) Q_DECL_OVERRIDE;
};

#endif // CVARIABLEOUTPUTLISTVARIABLES_H
