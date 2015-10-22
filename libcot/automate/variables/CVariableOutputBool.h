#ifndef CVARIABLEOUTPUTBOOL_H
#define CVARIABLEOUTPUTBOOL_H

#include "CVariableBool.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputBool : public CVariableBool, public IVariableOutput
{
    Q_OBJECT

public:
    CVariableOutputBool(QObject *parent = Q_NULLPTR);
    CVariableOutputBool(const QMap<QString, QVariant> &mapVar);
    ~CVariableOutputBool();

    //IVariableOutput
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable
    QVariantMap serialize() Q_DECL_OVERRIDE;
    enumVariableType getType()const Q_DECL_OVERRIDE;
    enumVariableOrganType getOrganType() const Q_DECL_OVERRIDE;
    void setValue(bool);
    using CVariableBool::setValue;
    void setToBindedValue(const QVariant &) Q_DECL_OVERRIDE;
    void writeValue() Q_DECL_OVERRIDE;

protected:
    bool m_passive;

};

#endif // CVARIABLEOUTPUTBOOL_H
