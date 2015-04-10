#ifndef CACTIONCMDPOMPE_H
#define CACTIONCMDPOMPE_H

#include "IAction.h"

class CActionCmdPompe : public IAction
{
	Q_OBJECT

public:
	CActionCmdPompe(QObject *parent);
	CActionCmdPompe(const QVariantMap &);
	CActionCmdPompe();
	~CActionCmdPompe();

    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;

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
