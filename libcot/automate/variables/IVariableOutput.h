#ifndef IVariableOutput_H
#define IVariableOutput_H

#include "qstring.h"

#include "IVariable.h"

class CModelExtensionCard;
class IComObserver;

class IVariableOutput
{
public:
    virtual ~IVariableOutput() {}
    virtual CModelExtensionCard* getExtensionCard()const=0;
    virtual QString getOrganneName()const=0;
    virtual void setOrganne(CModelExtensionCard* ,const QString &)=0;
    virtual QString getOrganneAddr()const=0;
    virtual IComObserver* getComObserver()const=0;
    virtual IVariable* getIVariable()=0;

private:
    virtual void writeValue()=0;
    
};

#endif // IVariableOutput_H
