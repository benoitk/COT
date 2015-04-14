#ifndef IVARIABLE_H
#define IVARIABLE_H

#include <QVariant>

enum variableType{
		type_bool = 0,
		type_float,
		type_int,
		type_string,
		type_stream,
		type_unknow
};


//Interface pour toute les variables de l'automate
class CUnit;
class IVariable
{

public:
	
	virtual QString toString()=0;
	virtual int toInt()=0;
	virtual float toFloat() =0;
	virtual bool toBool()=0;
	virtual QString getLabel()const =0;
	virtual void setLabel(QString)=0;
	virtual void setValue(QVariant)=0;
	virtual QString getName()const=0;
	virtual void setName(const QString&)=0;
	virtual void addBind(IVariable*)=0;
	virtual void delBind(IVariable*)=0;
	virtual void setToBindedValue(QVariant)=0;
	virtual variableType getType()const=0;
	virtual void switchToUnit(CUnit*)=0;
	virtual void getUnit()=0;
	virtual bool isStreamRelated()const=0;
	virtual QString getRelatedStreamName()const=0;
	virtual bool isMeasureRelated()const=0;
	virtual QString getRelatedMeasureName()const=0;
	virtual bool isDisplay()const=0;
	virtual QLinkedList<IVariable*> getListOutBinds()const=0;
	virtual QLinkedList<IVariable*> getListInBinds()const=0;

	
	
	
private:
	
};

#endif // IVARIABLE_H
