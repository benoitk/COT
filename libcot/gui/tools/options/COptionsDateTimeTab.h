#ifndef COPTIONSDATETIMETAB_H
#define COPTIONSDATETIMETAB_H

#include "IOptionsTab.h"

namespace Ui {
class COptionsDateTimeTab;
}

class COptionsDateTimeTab : public IOptionsTab
{
    Q_OBJECT

public:
    explicit COptionsDateTimeTab(QWidget *parent = Q_NULLPTR);
    ~COptionsDateTimeTab();

private:
    Ui::COptionsDateTimeTab *ui;
};

#endif // COPTIONSDATETIMETAB_H
