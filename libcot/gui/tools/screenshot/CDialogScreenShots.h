#ifndef CDIALOGSCREENSHOTS_H
#define CDIALOGSCREENSHOTS_H

#include <CDialog.h>
#include "QTimer"

#include "cot_global.h"



class IVariableUIHandler;
class QAction;
class QLabel;
class LIBCOT_EXPORT CDialogScreenShots : public CDialog
{

    Q_OBJECT
public:
    static CDialogScreenShots* getInstance();

signals:

public slots:
    void slotBackTriggered();
    void slotTakeScreenShot();

private:
    bool isUSBKeyMounted() const;
    QString targetDirectory() const;
    explicit CDialogScreenShots();
    static CDialogScreenShots* singleton;
    QAction* m_actBack;
    QAction* m_actStartTimer;
    QAction* m_actStopTimer;
    QLabel* m_label;
    QTimer m_timer;
    int m_nbScreenshot;
};

#endif // CDIALOGSCREENSHOTS_H
