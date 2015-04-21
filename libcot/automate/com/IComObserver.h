#ifndef ICOMOBSERVER_H
#define ICOMOBSERVER_H

#include "qstring.h"

class IVariable;
class ICom;
class IComObserver
{

public:
    virtual ~IComObserver() {}
    virtual IVariable* getVariable(const QString &addr_var)const=0;
	virtual void setCom(ICom*)=0;


private:
	
};

#endif // ICOMOBSERVER_H
