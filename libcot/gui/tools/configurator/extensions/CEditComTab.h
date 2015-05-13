#ifndef CEDITCOMTAB_H
#define CEDITCOMTAB_H

#include "IConfiguratorEditTab.h"

class CEditComTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditComTab(QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;
};

#endif // CEDITCOMTAB_H
