#ifndef CACTIONCMDPOMPE_H
#define CACTIONCMDPOMPE_H

#include "IAction.h"

class CActionCmdPompe : public IAction
{
	Q_OBJECT

public:
	CActionCmdPompe(QObject *parent);
	CActionCmdPompe(QVariantMap);
	CActionCmdPompe();
	~CActionCmdPompe();

	int getTiming();	
	void setTiming(int);
	bool runAction();
	QString getName()const;
private:

	QString m_name;
	QString m_label;
	int m_numero;
	int m_vitesse;
	bool m_sens;
	bool m_nbPasTour;
	bool m_ctrlContinu;

	int m_timing;

};

#endif // CACTIONCMDPOMPE_H
