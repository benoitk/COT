#include "CAutomate.h"
#include "CControlerAutomate.h"
#include "qdebug.h"
CControlerAutomate::CControlerAutomate()
{

}

CControlerAutomate::~CControlerAutomate()
{
    m_automateThread.quit();
    m_automateThread.wait();
}

void CControlerAutomate::automateStopped(){

}
