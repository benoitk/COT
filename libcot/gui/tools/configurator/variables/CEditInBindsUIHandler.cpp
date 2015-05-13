#include "CEditInBindsUIHandler.h"
#include "CPushButton.h"

#include <QLabel>

CEditInBindsUIHandler::CEditInBindsUIHandler(CScrollableWidget *scrollable, QObject *parent)
    : IConfiguratorUIHandler(scrollable, parent)
{
}

CEditInBindsUIHandler::~CEditInBindsUIHandler()
{
}

QWidget *CEditInBindsUIHandler::createWidget(int column, IVariable *ivar)
{
    switch (column) {
    case 0: {
        QLabel *lab = new QLabel(tr("Source"), container());
        return lab;
    }
    case 1: {
        CPushButton *button = new CPushButton(container());
        button->setText(ivar->getLabel());
        button->setEnabled(false);
        return button;
    }
    }
    return Q_NULLPTR;
}
