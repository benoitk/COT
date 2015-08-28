#ifndef CDIALOGMAINTENANCE_H
#define CDIALOGMAINTENANCE_H

#include <QDialog>
#include "cot_global.h"
class CVerticalButtonBar;
class QHBoxLayout;
class QTabWidget;
class QLabel;
class IVariableUIHandler;
class IVariable;
/**
 * @brief This is the base class for dialogs.
 * Use CPCWindow::openModal or openExec to show it.
 */
class LIBCOT_EXPORT CDialogMaintenance : public QDialog
{
    Q_OBJECT
public:
    explicit CDialogMaintenance(QWidget *parent = Q_NULLPTR);

    void setTitle(const QString &title);
    void setMainWidget(QWidget *widget);

public slots:
    void slotUpdateLayout(QList<IVariable*> arg_listIVariable);
    void slotUpdateError(const QString& arg_error);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    CVerticalButtonBar *m_buttonBar;
    QTabWidget *m_tabWidget;
    QLabel* m_errorLabel;
    IVariableUIHandler* m_calibValueHandler;
};

#endif // CDIALOGMAINTENANCE_H
