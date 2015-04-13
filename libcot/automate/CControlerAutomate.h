#ifndef CCONTROLERAUTOMATE_H
#define CCONTROLERAUTOMATE_H

#include <QObject>
#include <qthread.h>
#include "../cot_global.h"
class COTWIDGETS_EXPORT CControlerAutomate : public QObject
{
	Q_OBJECT
private:
	QThread automateThread;
public:
	CControlerAutomate();
	~CControlerAutomate();

};

#endif
