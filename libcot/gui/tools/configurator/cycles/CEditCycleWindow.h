#ifndef CEDITCYCLEWINDOW_H
#define CEDITCYCLEWINDOW_H

#include <QWidget>

namespace Ui {
class CEditCycleWindow;
}

class IEditCycleTab;
class CEditCycleTab;
class CEditCycleStepsTab;
class ICycle;

class CEditCycleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CEditCycleWindow(ICycle *cycle, QWidget *parent = Q_NULLPTR);
    ~CEditCycleWindow();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotOkTriggered();
    void slotCancelTriggered();

private:
    ICycle *m_cycle;
    Ui::CEditCycleWindow *ui;
    CEditCycleTab *m_ceditCycleTab;
    CEditCycleStepsTab *m_ceditCycleStepsTab;

    void addTab(IEditCycleTab *tab, const QString &title);
};

#endif // CEDITCYCLEWINDOW_H
