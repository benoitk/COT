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
    CStepWidget *addStep(CStep *step);

    CStepWidget *stepWidgetAt(int index) const;
    QList<CStepWidget *> selectedSteps() const;
    void copySteps(const QList<CStepWidget *> &stepWidgets, float to);
    void moveSteps(const QList<CStepWidget *> &stepWidgets, float to);
    void reorderStepWidgets(CStepWidget *ensureVisibleStep = Q_NULLPTR);

private slots:
    void slotAddStep();
    void slotAddStopStep();
    void slotCopyTriggered();
    void slotMoveTriggered();
    void slotScrollToStopStep();
    void slotHandleStepChanged(float from, float to);
};

#endif // CEDITSTEPLISTTAB_H
