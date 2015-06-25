#include "CAutomate.h"
#include "CControlerAutomate.h"
#include "qdebug.h"
CControlerAutomate::CControlerAutomate()
{
    CAutomate *automate = CAutomate::getInstance();
    automate->moveToThread(&m_automateThread);
    automate->initConfig();

    connect(&m_automateThread, &QThread::started, automate, &CAutomate::slotStartAutomate);
//    connect(&m_automateThread, &QThread::finished, automate, &QObject::deleteLater);
    connect(&m_automateThread, &QThread::finished, this, &CControlerAutomate::automateStopped);
    m_automateThread.start();
}

CControlerAutomate::~CControlerAutomate()
{
    m_automateThread.quit();
    m_automateThread.wait();
}

void CControlerAutomate::automateStopped(){

}
