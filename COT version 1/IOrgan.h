#ifndef IORGAN_H
#define IORGAN_H


#include "qstring.h"
#include "qlist.h"

typedef enum organType{
		output_bool = 0,
		output_float,
		output_int,
		input_bool,
		input_float,
		input_int
};

class IVariable;
class IOrgan 
{

public:
	virtual QString getName()const=0;
	virtual void setName(QString)const=0;
	virtual organType getType()const=0;
	//adresse physique sur le materiel, varie selon protocol 
	virtual QString getAddress()const=0; 
	virtual void setAddress(QString)const=0;
	virtual QString toString()const=0;
	virtual QList<IVariable*> getListParamters()const=0;

private:
	
};

#endif // IORGAN_H
