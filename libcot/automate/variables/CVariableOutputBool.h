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
    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;

    void setValue(bool);
    using CVariableBool::setValue;

private:

    void writeValue() Q_DECL_OVERRIDE;

    bool m_passive;

};

#endif // CVARIABLEOUTPUTBOOL_H
