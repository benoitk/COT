#include "CAlarmsWindow.h"
#include "IVariableUIHandler.h"
#include "CAutomate.h"
#include "CDisplayConf.h"

#include <QLabel>
#include <QGridLayout>

CAlarmsWindow::CAlarmsWindow(QWidget *parent) :
    IWindow(parent)
{
    setupWindow();
}

void CAlarmsWindow::setupWindow()
{
    m_alarmsHandler = new IVariableUIHandler(scrollable(), this);
    updateAlarms();
    connect(CAutomate::getInstance(), &CAutomate::signalStreamsMeasuresChanged,
            this, &CAlarmsWindow::updateAlarms);
}

void CAlarmsWindow::updateAlarms()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenAlarms = displayConf->getListForScrenAlarms();
    m_alarmsHandler->layout(screenAlarms);
}




