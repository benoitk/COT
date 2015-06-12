#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include <QDialog>
#include "cot_global.h"
class CVerticalButtonBar;

/**
 * @brief This dialog displays a message for the user, and an OK button.
 * Use with CPCWindow::openModal to make it modal.
 */
class LIBCOT_EXPORT CMessageBox : public QDialog
{
    Q_OBJECT
public:
    explicit CMessageBox(const QString &message, QWidget *parent = Q_NULLPTR);
    ~CMessageBox();

private:
    QString m_message;
    CVerticalButtonBar *m_buttonBar;
};

#endif // CMESSAGEBOX_H
