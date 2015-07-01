#ifndef IVariableOutput_H
#define IVariableOutput_H

#include "qstring.h"

#include "IVariable.h"

class IOrgan;
class IComObserver;
class CModelExtensionCard;
class IVariableOutput
{
public:
    IVariableOutput();
    IVariableOutput(const QVariantMap&);
    virtual ~IVariableOutput();
    virtual IOrgan* getOrgan()const;
    virtual QString getOrganName()const;
    virtual void setOrgan(CModelExtensionCard* ,const QString &);
    virtual QString getOrganAddr()const;
//    virtual IComObserver* getComObserver()const;

    virtual IVariable* getIVariable()=0;


    virtual void writeValue()=0;

protected:
    IOrgan* m_organ;

};

#endif // IVariableOutput_H
