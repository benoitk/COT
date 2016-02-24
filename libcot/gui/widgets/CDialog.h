#ifndef CDIALOG_H
#define CDIALOG_H

#include <QDialog>
#include "cot_global.h"
class CVerticalButtonBar;
class QHBoxLayout;
class QTabWidget;

/**
 * @brief This is the base class for dialogs.
 * Use CPCWindow::openModal or openExec to show it.
 */
class LIBCOT_EXPORT CDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CDialog(QWidget *parent = Q_NULLPTR);
    ~CDialog();

    void setTitle(const QString &title);

    CVerticalButtonBar *buttonBar() const;

    void setMainWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


    CVerticalButtonBar *m_buttonBar;
    QHBoxLayout *m_pageLayout;
    QTabWidget *m_tabWidget;
};

#endif // CDIALOG_H
