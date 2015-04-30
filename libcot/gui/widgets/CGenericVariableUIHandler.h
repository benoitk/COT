#ifndef CGENERICVARIABLEUIHANDLER_H
#define CGENERICVARIABLEUIHANDLER_H

#include "CScrollableWidget.h"

class QAction;
class IVariableUIHandler;
class CGenericVariableUIHandler : public CScrollableWidget
{
    Q_OBJECT
public:
    explicit CGenericVariableUIHandler(QWidget *parent = Q_NULLPTR);
    ~CGenericVariableUIHandler();
    QAction *addVariable() const;
    void setAddVariable(QAction *addVariable);

    QAction *removeVariable() const;
    void setRemoveVariable(QAction *removeVariable);

    void setIVariableUIHandler(IVariableUIHandler *iVariableUIHandler);

private slots:
    void slotAddVariable();
    void slotRemoveVariable();

private:
    QAction *m_addVariable;
    QAction *m_removeVariable;
    IVariableUIHandler *m_iVariableUIHandler;
};

#endif // CGENERICVARIABLEUIHANDLER_H
