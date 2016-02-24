#ifndef CDIALOGCONFIRMATION_H
#define CDIALOGCONFIRMATION_H
#include "CDialog.h"

#include "cot_global.h"
class CVerticalButtonBar;
class QHBoxLayout;
class QTabWidget;
class QLabel;
class IVariable;

class LIBCOT_EXPORT  CDialogConfirmation : public CDialog
{
    Q_OBJECT
public:
    explicit CDialogConfirmation(const QString& message, QWidget *parent = Q_NULLPTR);

   void setConfirmationMessage(const QString&);

private:

    QLabel* m_confirmationMessage;
};

#endif // CDIALOGCONFIRMATION_H
