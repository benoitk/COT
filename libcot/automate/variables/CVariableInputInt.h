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

    enumVariableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;


    IVariable* readValue() Q_DECL_OVERRIDE;
private:



};

#endif // CVARIBALEINPUTINT_H
