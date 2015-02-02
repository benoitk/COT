#include "CAutomate.h"
#include "CControlerAutomate.h"

CControlerAutomate::CControlerAutomate()
{
	CAutomate *automate = new CAutomate;
    automate->moveToThread(&automateThread);
	connect(&automateThread, &QThread::finished, automate, &QObject::deleteLater);
	connect(&automateThread, &QThread::started, automate, &CAutomate::slotRunAutomate);
    automateThread.start();
}

CControlerAutomate::~CControlerAutomate()
{
	automateThread.quit();
	automateThread.wait();
}
