#ifndef CPCWINDOW_H
#define CPCWINDOW_H

#include <QWidget>
#include <QApplication>

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

    template <typename T>
    static void openModal() {
        QWidget *parent = QApplication::activeWindow();

        if (!parent) {
            Q_ASSERT(false);
            return;
        }

        T *window = new T(parent);
        window->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        window->setAttribute(Qt::WA_DeleteOnClose);
        window->setWindowModality(Qt::ApplicationModal);
        window->resize(parent->size());
        window->move(parent->pos());
        window->show();
    }

public slots:
    void retranslate();

protected:
    virtual void changeEvent(QEvent *event);

private slots:
    void slotUpdateAvailable(const QString &version);
    void slotUpdateTriggered();

private:
    Ui::CPCWindow *ui;
    CUpdateManager *m_updateManager;

    void addTab(IPCTab *tab, const QString &title);
    bool canShowUpdatePopup() const;
};

#endif // CPCWINDOW_H
