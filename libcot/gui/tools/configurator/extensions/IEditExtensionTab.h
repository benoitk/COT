#ifndef IEDITEXTENSIONTAB_H
#define IEDITEXTENSIONTAB_H

#include <QWidget>

#include "CVerticalButtonBar.h"
class IVariable;
class IEditExtensionTab : public QWidget
{
    Q_OBJECT
public:
    explicit IEditExtensionTab(QWidget *parent = Q_NULLPTR) : QWidget(parent) { }

    CVerticalButtonBar *buttonBar() const { return findChild<CVerticalButtonBar *>(); }

    virtual void applyProperties(IVariable *ivar) = 0;
signals:
    void signalOkTriggered();
    void signalCancelTriggered();
};

#endif // IEDITEXTENSIONTAB_H
