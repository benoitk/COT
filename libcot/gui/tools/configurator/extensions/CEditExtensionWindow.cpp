#include "CEditExtensionWindow.h"
#include "CEditGeneralTab.h"
#include "CEditComTab.h"
#include "CEditOrgansTab.h"

#include <IVariable.h>

CEditExtensionWindow::CEditExtensionWindow(QWidget *parent)
    : IConfiguratorEditWindow(QVariant(), parent)
{
    addTab(new CEditGeneralTab());
    addTab(new CEditComTab());
    addTab(new CEditGeneralTab());
    initBaseWindow();
}

void CEditExtensionWindow::slotRetranslate()
{
    setTabText(0, tr("General"));
    setTabText(1, tr("Com"));
    setTabText(2, tr("Organs"));
}

void CEditExtensionWindow::slotOkTriggered()
{
    //TODO
    close();
}

void CEditExtensionWindow::slotCancelTriggered()
{
    close();
}
