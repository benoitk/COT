#ifndef IVariableInput_H
#define IVariableInput_H

#include "qstring.h"

enum organneInputType{
		type_input_bool = 0,
		type_input_float,
		type_input_int,
		type_input_string,
		type_input_stream,
		type_input_unknow
};

class CModelExtensionCard;
class IComObserver;
class IVariable;
class IVariableInput
{
public:
	virtual ~IVariableInput() {}
	virtual CModelExtensionCard* getExtensionCard()const=0;
	virtual QString getOrganneName()const=0;
	virtual void setOrganne(CModelExtensionCard* ,QString)=0;
	virtual QString getOrganneAddr()const=0;
	virtual organneInputType getTypeOrganne()const=0;
	virtual IComObserver* getComObserver()const=0;
	virtual IVariable* getIVariable()=0;

private:

	virtual IVariable* readValue()=0;
	
};

#endif // IVariableInput_H
