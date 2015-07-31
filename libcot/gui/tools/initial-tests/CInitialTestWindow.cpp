#include "CInitialTestWindow.h"

#include "CVerticalButtonBar.h"
#include "CScrollableWidget.h"
#include "IVariableUIHandler.h"

#include "CAutomate.h"
#include "CDisplayConf.h"
#include "qaction.h"
#include "qlabel.h"
#include "StyleRepository.h"
#include <QHBoxLayout>

CInitialTestsWindow::CInitialTestsWindow(QWidget *parent) :
    CDialog(parent)

{
  setTitle(tr("Initial tests"));
  if (StyleRepository::screenSize() == StyleRepository::SevenInch)
      setFixedSize(QSize(800, 480));
  else
      setFixedSize(QSize(1024, 600));

  CScrollableWidget* widgetLeft = new  CScrollableWidget(this);
  CScrollableWidget* widgetRight = new  CScrollableWidget(this);
  QWidget* mainWidget = new QWidget(this);
  QHBoxLayout* hLayout = new QHBoxLayout(mainWidget);
  hLayout->addWidget(widgetLeft);
  hLayout->addWidget(widgetRight);

  setMainWidget(mainWidget);
  connect(buttonBar()->addAction(CToolButton::ScrollUp, widgetLeft->moveUp() ), &QAction::triggered
          , this, &CInitialTestsWindow::slotUpdateWindow);
  connect(buttonBar()->addAction(CToolButton::ScrollDown, widgetLeft->moveDown()), &QAction::triggered
          , this, &CInitialTestsWindow::slotUpdateWindow);
  connect(buttonBar()->addAction(CToolButton::ScrollUp, widgetRight->moveUp() ), &QAction::triggered
          , this, &CInitialTestsWindow::slotUpdateWindow);
  connect(buttonBar()->addAction(CToolButton::ScrollDown, widgetRight->moveDown()), &QAction::triggered
          , this, &CInitialTestsWindow::slotUpdateWindow);
  connect(buttonBar()->addAction(CToolButton::Back), &QAction::triggered, this, &CInitialTestsWindow::slotBackTriggered);

  m_testVarHandler = new IVariableUIHandler(widgetLeft, this);
  m_indicatorVarHandler = new IVariableUIHandler(widgetRight, this);
  slotUpdateWindow();
  connect(CAutomate::getInstance(), &CAutomate::signalDisplayUpdated,
          this, &CInitialTestsWindow::slotUpdateWindow);

}

void CInitialTestsWindow::slotBackTriggered()
{
    close();
}


void CInitialTestsWindow::slotUpdateWindow()
{
    CAutomate *automate = CAutomate::getInstance();
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenInitialTest = displayConf->getListInitialsTestVariablesTest();
    IVariablePtrList screenInitialIndicator = displayConf->getListInitialsTestVariablesIndicator();
    m_testVarHandler->layout(screenInitialTest);
    m_indicatorVarHandler->layout(screenInitialIndicator);
}
