#ifndef CACTIONCMDREADINPUT_H
#define CACTIONCMDREADINPUT_H

#include "IAction.h"

class IVariable;
class CModelExtensionCard;
class CActionCmdReadInput : public IAction
{
	Q_OBJECT

public:
	CActionCmdReadInput(QObject *parent);
	CActionCmdReadInput(QVariantMap);
	CActionCmdReadInput();
	~CActionCmdReadInput();

int getTiming();	
	void setTiming(int);
	bool runAction();
	QString getName()const;
private:

	QString m_name;
	QString m_label;
	QString m_extentionName;
	QString m_organneName;
	IVariable* m_variableDestination;
	CModelExtensionCard* m_extensionCard;
};

#endif // CACTIONCMDREADINPUT_H
