#ifndef CVARIABLEINPUTFLOAT_H
#define CVARIABLEINPUTFLOAT_H

#include "CVariableFloat.h"
#include "IVariableInput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableInputFloat : public CVariableFloat, public IVariableInput
{
    Q_OBJECT

public:
    CVariableInputFloat(CAutomate* arg_automate, QObject *parent = Q_NULLPTR);
    CVariableInputFloat(const QMap<QString, QVariant> &mapVar, CAutomate* arg_automate, QObject *parent);
    ~CVariableInputFloat();

    //IVariableInput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    enumVariableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    IVariable* readValue() Q_DECL_OVERRIDE;
private:




};

#endif // CVARIABLEINPUTFLOAT_H
