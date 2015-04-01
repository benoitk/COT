#ifndef CACTIONCMDRELAY_H
#define CACTIONCMDRELAY_H
#include "IAction.h"


class CActionCmdRelay : public IAction
{
	Q_OBJECT

public:

	CActionCmdRelay(QObject *parent);
	CActionCmdRelay(QVariantMap);
	CActionCmdRelay();
	~CActionCmdRelay();

	int getTiming();	
	void setTiming(int);
	bool runAction();
	QString getName()const;
private:

	QString m_label;
	int m_num_card_output;
	int m_card_id;
	int m_timing;
	QString m_name;
	
};

#endif // CACTIONCMDRELAY_H
