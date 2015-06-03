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
    CModelExtensionCard* getExtensionCard()const Q_DECL_OVERRIDE;
    QString getOrganneName()const Q_DECL_OVERRIDE;
    QString getOrganneAddr()const Q_DECL_OVERRIDE;
    void setOrganne(CModelExtensionCard* , const QString &) Q_DECL_OVERRIDE;
    IComObserver* getComObserver()const Q_DECL_OVERRIDE;
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable




    QVariantMap serialise() Q_DECL_OVERRIDE;
    variableType getType()const Q_DECL_OVERRIDE;


    void setValue(float);

private:

    void writeValue() Q_DECL_OVERRIDE;
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;

};

#endif // CVARIABLEOUTPUTBOOL_H
