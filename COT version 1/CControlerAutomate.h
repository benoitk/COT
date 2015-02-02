#ifndef CCONTROLERAUTOMATE_H
#define CCONTROLERAUTOMATE_H

#include <QObject>
#include <qthread.h>
class CControlerAutomate : public QObject
{
	Q_OBJECT
private:
	QThread automateThread;
public:
	CControlerAutomate();
	~CControlerAutomate();

};

#endif