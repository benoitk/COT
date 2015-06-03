#ifndef CVARIABLEOUTPUTINT_H
#define CVARIABLEOUTPUTINT_H

#include "CVariableInt.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputInt : public CVariableInt, public IVariableOutput
{
    Q_OBJECT

public:
    CVariableOutputInt(QObject *parent = Q_NULLPTR);
    CVariableOutputInt(const QMap<QString, QVariant> &mapVar);
    ~CVariableOutputInt();

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

    void writeValue();
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;

};

#endif // CVARIABLEOUTPUTINT_H
