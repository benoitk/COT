#ifndef CMESSAGEBOX_H
#define CMESSAGEBOX_H

#include "CDialog.h"

/**
 * @brief This dialog displays a message for the user, and an OK button.
 * Use with CPCWindow::openModal to make it modal.
 */
class LIBCOT_EXPORT CMessageBox : public CDialog
{
    Q_OBJECT
public:
    explicit CMessageBox(const QString &message, QWidget *parent = Q_NULLPTR);
    ~CMessageBox();
};

#endif // CMESSAGEBOX_H
