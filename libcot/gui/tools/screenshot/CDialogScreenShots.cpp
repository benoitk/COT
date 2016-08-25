#include "CDialogScreenShots.h"

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
#include <QLabel>
#include "qdebug.h"
#include "QStorageInfo"
#include <QApplication>
#include <QPixmap>
#include <QDesktopWidget>

CDialogScreenShots* CDialogScreenShots::singleton = 0;

CDialogScreenShots::CDialogScreenShots() :
    CDialog() , m_label(new QLabel(this)), m_nbScreenshot(0)
{


  setTitle(tr("Screenshot tool"));
  if (StyleRepository::screenSize() == StyleRepository::SevenInch)
      setFixedSize(QSize(800, 480));
  else
      setFixedSize(QSize(1024, 600));


  m_label->setText(tr("Appuis sur play pour prendre 1 image/s"));
  setMainWidget(m_label);

  m_timer.setInterval(5000);

  m_actStopTimer = buttonBar()->addAction(CToolButton::Stop);
  connect(m_actStopTimer, &QAction::triggered, &m_timer, &QTimer::stop);

  m_actStartTimer = buttonBar()->addAction(CToolButton::Play);
  connect(m_actStartTimer, SIGNAL(triggered()), &m_timer, SLOT(start()));

  m_actBack = buttonBar()->addAction(CToolButton::Back);
  connect(m_actBack, &QAction::triggered, this, &CDialogScreenShots::slotBackTriggered);

  connect(&m_timer, &QTimer::timeout, this, &CDialogScreenShots::slotTakeScreenShot);


}
QString CDialogScreenShots::targetDirectory() const{
    QString target = QString::fromUtf8("%1/USB").arg(QString::fromUtf8(COT_USB_MOUNT_POINT));

    if (target.endsWith("/") && target != "/") {
        target.chop(1);
    }

    return target;
}
bool CDialogScreenShots::isUSBKeyMounted() const{
    QStorageInfo si(targetDirectory());
    si.refresh();
    return si.isReady() && si.isValid() && !si.name().isEmpty();
}

void CDialogScreenShots::slotTakeScreenShot(){
    if(isUSBKeyMounted()){
        m_label->setText("Ready pour prendre les images.\n Se balader et penser à venir couper à la fin");


        QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

        QString format = "png";
        QString fileName = targetDirectory() + tr("/screenshot")+ QString::number(++m_nbScreenshot)+"." + format;
        //QString fileName = "/Hard Disk2/screenshot" + QString::number(++m_nbScreenshot)+"." + format;
    qDebug() << "nom dossier" <<  fileName;
        if (!fileName.isEmpty())
            pixmap.save(fileName, "png", 100);


    }else{
        m_label->setText(tr("USB Key unmouted"));
    }
}

CDialogScreenShots* CDialogScreenShots::getInstance()
{
    if(!singleton)
            singleton = new CDialogScreenShots();

    return singleton;
}
void CDialogScreenShots::slotBackTriggered()
{
    close();
}
