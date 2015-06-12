#include "CAlarmsWindow.h"
#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QLabel>
#include <QGridLayout>

CAlarmsWindow::CAlarmsWindow(QWidget *parent) :
    IWindow(parent)
{
    m_alarmsHandler = new IVariableUIHandler(scrollable(), this);
    updateAlarms();
    connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
            this, &CAlarmsWindow::updateAlarms);
}

void CAlarmsWindow::updateAlarms()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenAlarms = displayConf->getListForScreenAlarms();
    m_alarmsHandler->layout(screenAlarms);
}




