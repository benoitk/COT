#ifndef CACTIONCMDPOMPE_H
#define CACTIONCMDPOMPE_H

#include "IAction.h"

class IVariable;
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
    QString getLabel()const Q_DECL_OVERRIDE;
	void setLabel(const QString&) Q_DECL_OVERRIDE;
    actionType getType()const Q_DECL_OVERRIDE;
private:

	QString m_name;

    QString m_label;
    //Rien ne nous assure les types correct dans le json (et rien ne contre indique à mettre n'importe quoi, normalement)
    
    IVariable* m_pump; //valeur par défaut de la pompe
	//valeur spécifique à l'action :
    IVariable* m_speed; 
	IVariable* m_nbStepOrTour;
	IVariable* m_clockwise;
	IVariable* m_stepOrTour;
	IVariable* m_cmdContinu;
};

#endif // CACTIONCMDPOMPE_H
