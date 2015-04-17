#ifndef CPCWINDOW_H
#define CPCWINDOW_H

#include <QWidget>

#include "cot_global.h"

namespace Ui {
class CPCWindow;
}

class IPCTab;
class CUpdateManager;

class LIBCOT_EXPORT CPCWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CPCWindow(QWidget *parent = Q_NULLPTR);
    ~CPCWindow();

private slots:
    void slotUpdateAvailable(const QString &version);
    void slotUpdateTriggered();

private:
    Ui::CPCWindow *ui;
    CUpdateManager *m_updateManager;

    void addTab(IPCTab *tab, const QString &title);
    bool canShowUpdatePopup() const;

    template <typename T>
    void openModal() {
        T *window = new T(this);
        window->setWindowFlags(Qt::Window);
        window->setAttribute(Qt::WA_DeleteOnClose);
        window->setWindowModality(Qt::ApplicationModal);
        window->resize(size());
        window->move(pos());
        window->show();
    }
};

#endif // CPCWINDOW_H
