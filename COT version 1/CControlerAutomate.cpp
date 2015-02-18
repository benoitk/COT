#include "CAutomate.h"
#include "CControlerAutomate.h"

CControlerAutomate::CControlerAutomate()
{
	CAutomate *automate = CAutomate::getInstance();
	automate->initConfig();
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
