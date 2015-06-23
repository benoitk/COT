#ifndef CVARIABLEOUTPUTLISTVARIABLES_H
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
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;
    void setValue(const QVariant & value) Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;
    void switchToUnit(CUnit*) Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;

    IVariable* getVariable(const QString&);
    void addVaraiable(IVariable*);

private:

    void writeValue() Q_DECL_OVERRIDE;


};

#endif // CVARIABLEOUTPUTLISTVARIABLES_H
