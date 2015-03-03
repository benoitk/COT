#ifndef CMODELEXTENSIONCARD_H
#define CMODELEXTENSIONCARD_H

#include "IComObserver.h"

#include <QObject>
#include "qmap.h"
#include "qvariant.h"

class ICom;
class IVariableInput;
class CModelExtensionCard : public QObject, public IComObserver
{
	Q_OBJECT

public:
	CModelExtensionCard(QObject *parent);
	~CModelExtensionCard();

	bool organneIsAvailabe(QString);
	QString getName()const;
	QVariant readOrganneValue(IVariableInput*);

	//IComObserver
	IVariable* getVariable(QString addr_var)const;
	void setCom(ICom*);

private:
	
	//qmap<name, type>
	QMap<QString, QString> m_organnes;
	ICom* m_interfaceCom;

	QString m_name;

};

#endif // CMODELEXTENSIONCARD_H
