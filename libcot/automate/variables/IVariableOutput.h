#ifndef IVariableOutput_H
#define IVariableOutput_H

#include "qstring.h"

enum organneOutputType{
		type_output_bool = 0,
		type_output_float,
		type_output_int,
		type_output_string,
		type_output_stream,
		type_output_unknow
};

class CModelExtensionCard;
class IComObserver;
class IVariable;
class IVariableOutput
{

public:
	
	virtual CModelExtensionCard* getExtensionCard()const=0;
	virtual QString getOrganneName()const=0;
	virtual void setOrganne(CModelExtensionCard* ,QString)=0;
	virtual QString getOrganneAddr()const=0;
	virtual organneOutputType getTypeOrganne()const=0;
	virtual IComObserver* getComObserver()const=0;
	virtual IVariable* getIVariable()=0;

private:
	virtual void writeValue()=0;
	
};

#endif // IVariableOutput_H
