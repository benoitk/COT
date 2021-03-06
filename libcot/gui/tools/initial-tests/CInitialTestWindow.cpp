#include "CInitialTestWindow.h"

#include "CVerticalButtonBar.h"
#include "CScrollableWidget.h"
#include "IVariableUIHandler.h"

#include "CAutomate.h"
#include "CScheduler.h"
#include "CDisplayConf.h"
#include "qaction.h"
#include "qlabel.h"
#include "StyleRepository.h"
#include <QHBoxLayout>
#include "CVariableAlarm.h"

CInitialTestsWindow::CInitialTestsWindow(CAutomate* arg_automate,QWidget *parent)
    : CDialog(parent)
    , m_automate(arg_automate)

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
  QAction* actMoveUpLeft = buttonBar()->addAction(CToolButton::ScrollUp, widgetLeft->moveUp());
  connect( actMoveUpLeft, &QAction::triggered, widgetRight->moveUp(), &QAction::triggered);
  connect(actMoveUpLeft, &QAction::triggered, this, &CInitialTestsWindow::slotUpdateWindow);

  QAction* actMoveDownLeft = buttonBar()->addAction(CToolButton::ScrollDown, widgetLeft->moveDown());
  connect(actMoveDownLeft, &QAction::triggered, widgetRight->moveDown(), &QAction::triggered);
  connect(actMoveDownLeft, &QAction::triggered, this, &CInitialTestsWindow::slotUpdateWindow);

  m_actBack = buttonBar()->addAction(CToolButton::Back);
  connect(m_actBack, &QAction::triggered, this, &CInitialTestsWindow::slotBackTriggered);
  connect(m_actBack, &QAction::triggered, m_automate->getScheduler(), &CScheduler::signalGetReadyForPlayCycleMesure);

  m_testVarHandler = new IVariableUIHandler(arg_automate, widgetLeft, this);
  m_indicatorVarHandler = new IVariableUIHandler(arg_automate, widgetRight, this);
  slotUpdateWindow();
  connect(m_automate, &CAutomate::signalDisplayUpdated,
          this, &CInitialTestsWindow::slotUpdateWindow);

  //init tout les relais au démarage, toutes cartes confondues
  foreach(IVariable* var, m_automate->getMapVariables()){
      if(var->getOrganType() == e_type_organ_output && (var->getType() == e_type_bool || var->getType() == e_type_alarm)){
          (dynamic_cast<IVariableOutput*>(var))->writeValue();
      }
  }

  //et des alarm des init qui doivent toujours être à faux au démarage.
  //problème pour les alarm dans l'init qui ont l'autoacquit à false
  foreach(IVariable* var, m_automate->getDisplayConf()->getListInitialsTestVariablesTest()){
        var->setValue(true);
        if(var->getType() == e_type_alarm)
            dynamic_cast<CVariableAlarm*>(var)->deconnectFromAutomate();
  }
  m_automate->getScheduler()->slotStartAllCyleAutonome();
  m_timerTests.singleShot(1000, this, SLOT(slotTests()));

}

void CInitialTestsWindow::slotBackTriggered()
{
   m_automate->acquitAlarms();
    foreach(IVariable* var, m_automate->getDisplayConf()->getListInitialsTestVariablesTest()){
          if(var->getType() == e_type_alarm)
              dynamic_cast<CVariableAlarm*>(var)->connectFromAutomate();
    }
    close();
}


void CInitialTestsWindow::slotUpdateWindow()
{
    CAutomate *automate = m_automate;
    CDisplayConf *displayConf = automate->getDisplayConf();
    IVariablePtrList screenInitialTest = displayConf->getListInitialsTestVariablesTest();
    IVariablePtrList screenInitialIndicator = displayConf->getListInitialsTestVariablesIndicator();
    m_testVarHandler->layout(screenInitialTest);
    m_indicatorVarHandler->layout(screenInitialIndicator);
}

void CInitialTestsWindow::slotTests(){
    bool test = true;
    foreach(IVariable* var, m_automate->getDisplayConf()->getListInitialsTestVariablesTest()){
        if(var->toBool())
            test = false;

    }
    if(test)
        emit m_actBack->triggered();
    else m_timerTests.singleShot(1000, this, SLOT(slotTests()));
;
}
