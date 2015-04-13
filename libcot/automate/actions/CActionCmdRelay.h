#ifndef CACTIONCMDRELAY_H
#define CACTIONCMDRELAY_H
#include "IAction.h"


class CActionCmdRelay : public IAction
{
	Q_OBJECT

public:

	CActionCmdRelay(QObject *parent);
    CActionCmdRelay(const QVariantMap&);
	CActionCmdRelay();
	~CActionCmdRelay();

	int getTiming();	
	void setTiming(int);
    bool runAction() Q_DECL_OVERRIDE;
    QString getName()const Q_DECL_OVERRIDE;
    QList<IVariable*> getListParameters()const Q_DECL_OVERRIDE;
private:

	QString m_label;
	int m_num_card_output;
	int m_card_id;
	int m_timing;
	QString m_name;
	
};

#endif // CACTIONCMDRELAY_H
