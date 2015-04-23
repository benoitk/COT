#ifndef IVariableInput_H
#define IVariableInput_H

#include "qstring.h"

#include "IVariable.h"

class CModelExtensionCard;
class IComObserver;

class IVariableInput
{
public:
	virtual ~IVariableInput() {}
	virtual CModelExtensionCard* getExtensionCard()const=0;
	virtual QString getOrganneName()const=0;
	virtual void setOrganne(CModelExtensionCard* ,QString)=0;
	virtual QString getOrganneAddr()const=0;
	virtual IComObserver* getComObserver()const=0;
	virtual IVariable* getIVariable()=0;

private:

	virtual IVariable* readValue()=0;
	
};

#endif // IVariableInput_H
