#ifndef IORGAN_H
#define IORGAN_H


#include "qstring.h"

typedef enum organType{
		output_bool = 0,
		output_float,
		output_int,
		input_bool,
		input_float,
		input_int
};

class IOrgan 
{

public:
	virtual QString getName()const=0;
	virtual organType getType()const=0;
	virtual QString getAddress()const=0;
	virtual QString toString()const=0;

private:
	
};

#endif // IORGAN_H
