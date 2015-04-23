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

    static void openModal(QWidget *widget, const QRect &geometry) {
        widget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        widget->setAttribute(Qt::WA_DeleteOnClose);
        widget->setWindowModality(Qt::ApplicationModal);
        widget->setGeometry(geometry);
        widget->show();
    }

    template <typename T>
    static void openModal() {
        QWidget *parent = QApplication::activeWindow();

        if (!parent) {
            Q_ASSERT(false);
            return;
        }

        T *window = new T(parent);
        openModal(window, QRect(parent->pos(), parent->size()));
    }

    template <typename T, typename Arg>
    static void openModal(const Arg &arg) {
        QWidget *parent = QApplication::activeWindow();

        if (!parent) {
            Q_ASSERT(false);
            return;
        }

        T *window = new T(arg, parent);
        openModal(window, QRect(parent->pos(), parent->size()));
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
