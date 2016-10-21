#ifndef CEDITSTEPLISTTAB_H
#define CEDITSTEPLISTTAB_H

#include "IConfiguratorEditTab.h"

class ICycle;
class CStep;
class CStepWidget;
class QVBoxLayout;
class CScrollablePagerWidget;
class CGenericVariablesEditor;

/*
Duplication feature = multi-select contiguous steps (e.g. from step 3 to step 6),
and copy/paste elsewhere in the (same) cycle (e.g. starting from step 10 --> 10 to 13).
Move feature = change from step 3 to step 6 to step 10 --> step 10 to step 13.
In both cases, if there's any step (in 10, 11, 12 or 13) in the middle of the insertion range (10-13),
they should be moved to after the inserted range (e.g. 14, 15, 16, 17), by moving everything after the
inserted range by the same offset (e.g. 25 becomes 28). But this logic should be in the automat.
=> needs API in cycle for copy(begin, end, destination) and API for move(begin, end, destination)
//TOUT Le principe d'édition est a refaire.

*/
class CAutomate;
class CEditStepListTab : public IConfiguratorEditTab
{
    Q_OBJECT

public:
    explicit CEditStepListTab(CAutomate* arg_automate, ICycle *cycle, QWidget *parent = Q_NULLPTR);

    void applyProperties(const QVariant &object) Q_DECL_OVERRIDE;

    static bool validateStepWidget(CGenericVariablesEditor *editor, void *userData1, void *userData2);

private:
    CScrollablePagerWidget *m_widget;
    QVBoxLayout *m_layout;
    ICycle* m_cycle;

    void ensureStepWidgetVisible(CStepWidget *stepWidget);
    CStepWidget *addStep(CStep *step);

    CStepWidget *stepWidgetAt(int index) const;
    QList<CStepWidget *> selectedSteps() const;
    void copySteps(const QList<CStepWidget *> &stepWidgets, float to);
    void moveSteps(const QList<CStepWidget *> &stepWidgets, float to);
    void reorderStepWidgets(CStepWidget *ensureVisibleStep = Q_NULLPTR);
    bool hasExistingInterval(float interval, CStepWidget *byPass = Q_NULLPTR) const;

    CAutomate* m_automate;

private slots:
    void slotMoveUp();
    void slotMoveDown();
    void slotAddStep();
    void slotAddStopStep();
    void slotCopyTriggered();
    void slotMoveTriggered();
    void slotScrollToStopStep();
    void slotHandleStepChanged(float from, float to);
    void slotHandleDeleteRequest();
    void slotDeleteAll();
};

#endif // CEDITSTEPLISTTAB_H
