#ifndef CEDITORGANSTAB_H
#define CEDITORGANSTAB_H

#include "IConfiguratorEditTab.h"

class CEditOrgansTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditOrgansTab(QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;
};

#endif // CEDITORGANSTAB_H
