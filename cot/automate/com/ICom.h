#ifndef ICom_H
#define ICom_H

#include <QObject>
#include "qvariant.h"

enum comType{
		type_tcp = 0,
		type_jbus,
		type_jbus_over_tcpip,
		
};

class IVariableInput;
class IVariableOutput;
class ICom : public QObject
{
	Q_OBJECT

public:
	ICom(QObject *parent);
	~ICom();

	virtual QVariant readData()=0;
	virtual QVariant readData(IVariableInput*)=0;

	virtual void writeData(IVariableOutput*)=0;
	virtual void addVariableOnDataTable(IVariableInput*)=0;
	virtual void addVariableOnDataTable(IVariableOutput*)=0;

	virtual void triggerUpdateAllData()=0;
	virtual ICom* getType()const=0;

private:
	
};

#endif // ICom_H
