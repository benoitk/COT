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

    CModelExtensionCard* getExtensionCard()const Q_DECL_OVERRIDE;
    QString getOrganneName()const Q_DECL_OVERRIDE;
    QString getOrganneAddr()const Q_DECL_OVERRIDE;
    void setOrganne(CModelExtensionCard* , const QString &) Q_DECL_OVERRIDE;
    IComObserver* getComObserver()const Q_DECL_OVERRIDE;
    IVariable* getIVariable() Q_DECL_OVERRIDE;

    //IVariable

    variableType getType()const Q_DECL_OVERRIDE;
    QVariantMap serialise() Q_DECL_OVERRIDE;

private:


    IVariable* readValue() Q_DECL_OVERRIDE;
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;


};

#endif // CVARIABLEINPUTBOOL_H
