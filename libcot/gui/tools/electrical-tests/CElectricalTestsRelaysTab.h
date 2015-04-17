#ifndef CELECTRICALTESTSRELAYSTAB_H
#define CELECTRICALTESTSRELAYSTAB_H

#include "IElectricalTestsTab.h"

namespace Ui {
class CElectricalTestsRelaysTab;
}

class CElectricalTestsRelaysTab : public IElectricalTestsTab
{
    Q_OBJECT

public:
    explicit CElectricalTestsRelaysTab(QWidget *parent = Q_NULLPTR);
    ~CElectricalTestsRelaysTab();

private:
    Ui::CElectricalTestsRelaysTab *ui;
};

#endif // CELECTRICALTESTSRELAYSTAB_H
