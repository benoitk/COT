#ifndef IVariableOutput_H
#define IVariableOutput_H

#include "qstring.h"

#include "IVariable.h"

class CModelExtensionCard;
class IComObserver;

class IVariableOutput
{
public:
    IVariableOutput();
    virtual CModelExtensionCard* getExtensionCard()const;
    virtual QString getOrganneName()const;
    virtual void setOrganne(CModelExtensionCard* ,const QString &);
    virtual QString getOrganneAddr()const;
    virtual IComObserver* getComObserver()const;

    virtual IVariable* getIVariable()=0;

private:
    virtual void writeValue()=0;

protected:
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;

};

#endif // IVariableOutput_H
