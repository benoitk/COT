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
    enumVariableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;

private:

    //IVariableInput
    IVariable* readValue() Q_DECL_OVERRIDE;



};

#endif // CVARIABLEINPUTBOOL_H
