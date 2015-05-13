#ifndef CEDITEXTENSIONWINDOW_H
#define CEDITEXTENSIONWINDOW_H

#include "IConfiguratorEditWindow.h"

class CEditExtensionWindow : public IConfiguratorEditWindow
{
    Q_OBJECT

public:
    explicit CEditExtensionWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void slotRetranslate();
    void slotOkTriggered();
    void slotCancelTriggered();
};

#endif // CEDITEXTENSIONWINDOW_H
