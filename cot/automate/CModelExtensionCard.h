#ifndef CMODELEXTENSIONCARD_H
#define CMODELEXTENSIONCARD_H

#include "IComObserver.h"

#include <QObject>
#include "qlist.h"
#include "qvariant.h"

class ICom;
class IVariableInput;
class IOrgan;
class CModelExtensionCard : public QObject, public IComObserver
{
	Q_OBJECT

public:
	CModelExtensionCard(QObject *parent);
	~CModelExtensionCard();

	bool organneIsAvailabe(QString);
	QString getName()const;
	QVariant readOrganneValue(IVariableInput*);

	QList<IOrgan*>  getListOrgan()const;
	QString getLabel()const;
	ICom* getICom()const;



	//IComObserver
	IVariable* getVariable(QString addr_var)const;
	void setCom(ICom*);


private:
	
	//qmap<name, type>

	QList<IOrgan*> m_listOrgan;
	ICom* m_interfaceCom;
	
	QString m_lbl;
	QString m_name;

};

#endif // CMODELEXTENSIONCARD_H
