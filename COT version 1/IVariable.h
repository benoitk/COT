#ifndef IVARIABLE_H
#define IVARIABLE_H

#include <QObject>
#include "qvariant.h"
//Interface pour toute les variables de l'automate
class IVariable : public QObject
{
	Q_OBJECT

public:
	IVariable(QObject* parent);
	IVariable();
	virtual QString toString()const =0;
	virtual int toInt()const=0;
	virtual float toFloat()const =0;
	virtual QString getLabel()const =0;
	virtual void setLabel(QString)=0;
	virtual void setValue(QVariant)=0;
	//virtual QString getName()const=0;
	
private:
	
};

#endif // IVARIABLE_H
