#ifndef CPCWINDOW_H
#define CPCWINDOW_H

#include <QDialog>
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

    static int openExec(QDialog *dialog) {
        QWidget *parent = QApplication::activeWindow();

        if (!parent) {
            Q_ASSERT(false);
            return QDialog::Rejected;
        }

#ifdef QT_DEBUG
        // add windows decorations when debugging
        dialog->setWindowFlags(Qt::Dialog);
#else
        dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
#endif
        dialog->adjustSize();
        QRect rect = QRect(QPoint(), dialog->minimumSize());
        rect.moveCenter(parent->geometry().center());
        dialog->setGeometry(rect);
        return dialog->exec();
    }

    static void openModal(QWidget *widget, const QRect &geometry) {
#ifdef QT_DEBUG
        // add windows decorations when debugging
        widget->setWindowFlags(Qt::Window);
#else
        widget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
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
