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

    int m_address;
    variableAccess m_access;
    IVariable* readValue() Q_DECL_OVERRIDE;
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;


};

#endif // CVARIBALEINPUTINT_H
