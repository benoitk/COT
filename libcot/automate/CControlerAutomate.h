#ifndef CCONTROLERAUTOMATE_H
#define CCONTROLERAUTOMATE_H

#include <QObject>
#include <qthread.h>

#ifndef NOT_SHAREDLIB
#include "../cot_global.h"
class COTWIDGETS_EXPORT CControlerAutomate : public QObject
#else
class CControlerAutomate : public QObject
#endif
{
	Q_OBJECT
private:
	QThread automateThread;
public:
	CControlerAutomate();
	~CControlerAutomate();

};

#endif
