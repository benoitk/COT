#ifndef CACTIONUNKNOW_H
#define CACTIONUNKNOW_H

#include "IAction.h"

class CActionUnknow : public IAction
{
	Q_OBJECT

public:
	CActionUnknow(QObject *parent);
	CActionUnknow(QVariantMap mapAction);
	~CActionUnknow();

	bool runAction();
	QString getName()const;

private:
	QString m_name;
	QString m_label;
};

#endif // CACTIONUNKNOW_H
