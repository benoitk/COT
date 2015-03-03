#ifndef ICom_H
#define ICom_H

#include <QObject>
#include "qvariant.h"

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


private:
	
};

#endif // ICom_H
