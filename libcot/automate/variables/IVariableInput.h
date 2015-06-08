#ifndef IVariableInput_H
#define IVariableInput_H

#include "qstring.h"

#include "IVariable.h"

class CModelExtensionCard;
class IComObserver;

class IVariableInput
{
public:
    IVariableInput();
    virtual ~IVariableInput();
    virtual CModelExtensionCard* getExtensionCard()const;
    virtual QString getOrganneName()const;
    virtual void setOrganne(CModelExtensionCard* ,const QString &);
    virtual QString getOrganneAddr()const;
    virtual IComObserver* getComObserver()const;

    virtual IVariable* getIVariable()=0;

private:
    virtual IVariable* readValue()=0;

protected:
    CModelExtensionCard* m_modelExtensionCard;
    QString m_organneName;
    QString m_organneAddr;

};

#endif // IVariableInput_H
