#ifndef CUPDATEDIALOG_H
#define CUPDATEDIALOG_H

#include "CDialog.h"

namespace Ui {
class CUpdateDialog;
}

class CUpdateManager;
class QAbstractButton;

class LIBCOT_EXPORT CUpdateDialog : public CDialog
{
    Q_OBJECT

public:
    explicit CUpdateDialog(CUpdateManager *updateManager, QWidget *parent = Q_NULLPTR);
    ~CUpdateDialog();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotPerformUpdate();
    void slotError(const QString &error);
    void slotFinished(bool success);

private:
    Ui::CUpdateDialog *ui;
    CUpdateManager *m_updateManager;
};

#endif // CUPDATEDIALOG_H
