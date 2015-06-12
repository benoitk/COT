#ifndef CDIALOG_H
#define CDIALOG_H

#include <QDialog>
#include "cot_global.h"
class CVerticalButtonBar;
class QHBoxLayout;

/**
 * @brief This is the base class for dialogs.
 * Use CPCWindow::openModal or openExec to show it.
 */
class LIBCOT_EXPORT CDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CDialog(const QString &title, QWidget *parent = Q_NULLPTR);
    ~CDialog();

    CVerticalButtonBar *buttonBar() const;

    void setMainWidget(QWidget *widget);

private:
    CVerticalButtonBar *m_buttonBar;
    QHBoxLayout *m_pageLayout;
};

#endif // CDIALOG_H
