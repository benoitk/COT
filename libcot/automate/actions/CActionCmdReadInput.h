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
    CActionCmdReadInput(const QVariantMap&);
	CActionCmdReadInput();
	~CActionCmdReadInput();

    int getTiming();
	void setTiming(int);
    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
private:

	QString m_name;
	QString m_label;
	QString m_extentionName;
	QString m_organneName;
	IVariable* m_variableDestination;
	CModelExtensionCard* m_extensionCard;
};

#endif // CACTIONCMDREADINPUT_H
