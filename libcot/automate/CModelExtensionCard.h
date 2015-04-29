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
	//Use for API
	QList<IOrgan*>  getListOrgans()const;
	QString getLabel()const;
	ICom* getICom()const;

	//
	CModelExtensionCard(QObject *parent);
	~CModelExtensionCard();

	QString getName()const;
	QVariant readOrganneValue(IVariableInput*);




	//IComObserver
    IVariable* getVariable(const QString &addr_var)const Q_DECL_OVERRIDE;
    void setCom(ICom*) Q_DECL_OVERRIDE;


private:
	
	//qmap<name, type>

	QList<IOrgan*> m_listOrgans;
	ICom* m_interfaceCom;
	
	QString m_lbl;
	QString m_name;

};

#endif // CMODELEXTENSIONCARD_H
