#ifndef CVARIABLEINPUTBOOL_H
#define CVARIABLEINPUTBOOL_H

#include "IVariableInput.h"
#include "CVariableBool.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputBool : public CVariableBool, public IVariableInput
{
    Q_OBJECT

public:
    CVariableInputBool(QObject *parent = Q_NULLPTR);
    CVariableInputBool(const QMap<QString, QVariant> &mapVar);
    ~CVariableInputBool();

    //IVariableInput
    IVariable* getIVariable() Q_DECL_OVERRIDE;


    //IVariable

    variableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;
    VariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    QVariant toVariant() Q_DECL_OVERRIDE;
    QString toString() Q_DECL_OVERRIDE;
    int toInt() Q_DECL_OVERRIDE;
    float toFloat() Q_DECL_OVERRIDE;
    bool toBool() Q_DECL_OVERRIDE;

private:

    //IVariableInput
    IVariable* readValue() Q_DECL_OVERRIDE;



};

#endif // CVARIABLEINPUTBOOL_H
