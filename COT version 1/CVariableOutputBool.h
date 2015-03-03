#ifndef CVARIABLEOUTPUTBOOL_H
#define CVARIABLEOUTPUTBOOL_H

#include "IVariable.h"
#include "IVariableOutput.h"

#include <qobject.h>
#include "qlinkedlist.h"

class CVariableOutputBool : public QObject, public IVariable, public IVariableOutput
{
	Q_OBJECT

public:
	CVariableOutputBool(QObject *parent);
	CVariableOutputBool(QMap<QString, QVariant> mapVar);
	~CVariableOutputBool();

	//IVariableOutput
	CModelExtensionCard* getExtensionCard()const;
	QString getOrganneName()const;
	QString getOrganneAddr()const;
	void setOrganne(CModelExtensionCard* ,QString);
	organneOutputType getTypeOrganne()const;
	IComObserver* getComObserver()const;
	IVariable* getIVariable();

	//IVariable
	QString toString();
	int toInt();
	float toFloat();
	bool toBool();
	void setValue(float);
	void setValue(QVariant);
	QString getLabel()const;
	void setLabel(QString);
	//QString getName()const;
	void addBind(IVariable*);
	void setToBindedValue(QVariant);
	variableType getType()const;
private:
	void writeValue();
	CModelExtensionCard* m_modelExtensionCard;
	QString m_organneName;
	QString m_organneAddr;

	bool m_bValeur;
	QString m_label;
	QLinkedList<IVariable*> m_listBinds;
	
	organneOutputType m_organneType;
};

#endif // CVARIABLEOUTPUTBOOL_H
