#ifndef IACTION_H
#define IACTION_H

#include <QObject>

class IAction : public QObject
{
	Q_OBJECT

public:
	IAction(QObject *parent);
	IAction();
	~IAction();

	virtual bool runAction()=0;
	virtual QString getName()const=0;

	//static IAction* factory(QVariantMap);

};

#endif // IACTION_H
