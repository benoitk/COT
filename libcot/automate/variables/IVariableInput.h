#ifndef IVariableInput_H
#define IVariableInput_H

#include "qstring.h"

#include "IVariable.h"

class CModelExtensionCard;
class IComObserver;
class IOrgan;
class IVariableInput
{
public:
    IVariableInput();
    IVariableInput(const QVariantMap & mapVar);
    virtual ~IVariableInput();
    virtual IOrgan* getOrgan()const;
    virtual QString getOrganName()const;
    virtual void setOrgan(CModelExtensionCard* ,const QString &);
    virtual QString getOrganAddr()const;
//    virtual IComObserver* getComObserver()const;

    virtual IVariable* getIVariable()=0;
    virtual IVariable* readValue()=0;
private:


protected:
    IOrgan* m_organ;

};

#endif // IVariableInput_H
