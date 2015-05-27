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

class LIBCOT_EXPORT CPCWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CPCWindow(QWidget *parent = Q_NULLPTR);
    ~CPCWindow();

    static int openExec(QDialog *dialog);

    template <typename T>
    static void openExec() {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(parent);
        openExec(window);
        delete window;
    }

    static void openModal(QWidget *widget);

    template <typename T>
    static void openModal() {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(parent);
        openModal(window);
    }

    template <typename T, typename Arg>
    static void openModal(const Arg &arg) {
        QWidget *parent = QApplication::activeWindow();
        T *window = new T(arg, parent);
        openModal(window);
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
