#ifndef CEDITVARIABLETAB_H
#define CEDITVARIABLETAB_H

#include "IEditVariableTab.h"
namespace Ui {
class CEditVariableTab;
}
class CEditVariableTabUIHandler;
class IVariable;
class CEditVariableTab : public IEditVariableTab
{
    Q_OBJECT
public:
    explicit CEditVariableTab(QWidget *parent = Q_NULLPTR);
    ~CEditVariableTab();
    void setVariables(const QString &variableName);
private:
    Ui::CEditVariableTab *ui;
    CEditVariableTabUIHandler *m_configuratorUIHandler;
};

#endif // CEDITVARIABLETAB_H
