#ifndef CEDITSTEPLISTTAB_H
#define CEDITSTEPLISTTAB_H

#include "IConfiguratorEditTab.h"

class ICycle;
class CStep;
class CStepWidget;
class QVBoxLayout;

class CEditStepListTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditStepListTab(ICycle *cycle, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

private:
    QWidget *m_widget;
    QVBoxLayout *m_layout;

    void ensureStepWidgetVisible(CStepWidget *stepWidget);
    CStepWidget *addStep(CStep *step, bool ensureVisible);

private slots:
    void slotAddStep();
    void slotAddStopStep();
    void slotScrollToStopStep();
};

#endif // CEDITSTEPLISTTAB_H
