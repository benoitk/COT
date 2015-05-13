#include "CEditComTab.h"
#include "CScrollableWidget.h"
#include "CVerticalButtonBar.h"

#include <CAutomate.h>

CEditComTab::CEditComTab(QWidget *parent)
    : IConfiguratorEditTab(parent)
{
    initBaseTab();
}

void CEditComTab::applyProperties(const QVariant &object)
{
}
