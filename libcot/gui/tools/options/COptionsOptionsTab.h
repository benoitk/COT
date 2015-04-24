#ifndef COPTIONSOPTIONSTAB_H
#define COPTIONSOPTIONSTAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsOptionsTab;
}
class IVariableUIHandler;

class COptionsOptionsTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsOptionsTab(QWidget *parent = Q_NULLPTR);
    ~COptionsOptionsTab();

protected slots:
    void updateOptions();

private:
    Ui::COptionsOptionsTab *ui;
    IVariableUIHandler *m_optionHandler;
};

#endif // COPTIONSOPTIONSTAB_H
