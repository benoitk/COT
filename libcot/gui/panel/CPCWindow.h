#ifndef CPCWINDOW_H
#define CPCWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QApplication>

#include "cot_global.h"
#include "CVerticalButtonBar.h"

namespace Ui {
class CPCWindow;
}

class IPCTab;
class CUpdateManager;
class CDialog;

class LIBCOT_EXPORT CPCWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CPCWindow(QWidget *parent = Q_NULLPTR);
    ~CPCWindow();

    static int openExec(CDialog *dialog);

    template <typename T>
    static void openExec() {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(parent);
        openExec(window);
        delete window;
    }

    template <typename T, typename Arg>
    static T* openExec(const Arg &arg) {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(arg, parent);
        openExec(window);
        return window;
    }

    static void openModal(QWidget *widget);

    template <typename T>
    static T* openModal() {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(parent);
        openModal(window);
        return window;
    }

    template <typename T, typename Arg>
    static T* openModal(const Arg &arg) {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(arg, parent);
        openModal(window);
        return window;
    }

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

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
