#ifndef ICOMOBSERVER_H
#define ICOMOBSERVER_H

#include "qstring.h"

class IVariable;
class ICom;
class IComObserver
{

public:
	virtual IVariable* getVariable(QString addr_var)const=0;
	virtual void setCom(ICom*)=0;


private:
	
};

#endif // ICOMOBSERVER_H
