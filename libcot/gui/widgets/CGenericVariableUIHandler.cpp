#include "CGenericVariableUIHandler.h"
#include "CScrollableWidget.h"
#include <IVariableUIHandler.h>
#include <QAction>
#include <QVBoxLayout>

CGenericVariableUIHandler::CGenericVariableUIHandler(QWidget *parent)
    : CScrollableWidget(parent),
      m_addVariable(Q_NULLPTR),
      m_removeVariable(Q_NULLPTR)
{
    m_addVariable = new QAction(tr("Add Variable..."), this);
    m_addVariable->setObjectName(QStringLiteral("addvariableaction"));
    connect(m_addVariable, &QAction::triggered, this, &CGenericVariableUIHandler::slotAddVariable);
    m_removeVariable = new QAction(tr("Remove Variable"), this);
    m_removeVariable->setObjectName(QStringLiteral("removevariableaction"));
    connect(m_removeVariable, &QAction::triggered, this, &CGenericVariableUIHandler::slotRemoveVariable);
}

CGenericVariableUIHandler::~CGenericVariableUIHandler()
{

}

QAction *CGenericVariableUIHandler::addVariable() const
{
    return m_addVariable;
}

QAction *CGenericVariableUIHandler::removeVariable() const
{
    return m_removeVariable;
}

void CGenericVariableUIHandler::slotAddVariable()
{
    //TODO
}

void CGenericVariableUIHandler::slotRemoveVariable()
{
    //TODO
}

void CGenericVariableUIHandler::setIVariableUIHandler(IVariableUIHandler *iVariableUIHandler)
{
    m_iVariableUIHandler = iVariableUIHandler;
    m_iVariableUIHandler->setScrollableWidget(this);
}
