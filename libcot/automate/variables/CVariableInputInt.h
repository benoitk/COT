#ifndef CVARIBALEINPUTINT_H
#define CVARIBALEINPUTINT_H

#include "CVariableInt.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"


class CVariableInputInt : public CVariableInt, public IVariableInput
{
    Q_OBJECT

public:
    CVariableInputInt(QObject *parent = Q_NULLPTR);
    CVariableInputInt(const QMap<QString, QVariant> &mapVar);
    ~CVariableInputInt();

//IVariableInput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable

    variableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;

private:

    IVariable* readValue() Q_DECL_OVERRIDE;

};

#endif // CVARIBALEINPUTINT_H
