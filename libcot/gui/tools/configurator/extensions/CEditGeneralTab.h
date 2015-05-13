#ifndef CEDITGENERALTAB_H
#define CEDITGENERALTAB_H

#include "IConfiguratorEditTab.h"

class CEditGeneralTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditGeneralTab(QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;
};

#endif // CEDITGENERALTAB_H
