#ifndef CPCWINDOW_H
#define CPCWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QApplication>

#include "CUserSession.h"
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
    static void openExec(QWidget *parent) {
        //QWidget *parent = QApplication::activeWindow();
        T *window = new T(parent);
        openExec(window);
        delete window;
    }

    template <typename T, typename Arg>
    static int openExec(const Arg &arg, QWidget* parent) {
        //TODO 0 chance que la dialog créé soit détruite un jour selon le parent.
        // Mais si on demande la même ça en recré une : mettre des singletons ou l'attribue deleteOnClose ?
        //QWidget *parent = QApplication::activeWindow(); //peu renvoyer un pointeur vide (cf sortie de réglage de l'heure)
        T *window = new T(arg, parent);

        return openExec(window);
    }

    static void openModal(QWidget *widget, bool arg_deleteOnClose = true);

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

    static bool showGraphInMainScreen();

public slots:
    void retranslate();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slotStreamsUpdated();
    void slotUpdateAvailable(const QString &version);
    void slotUpdateTriggered();

private:
    Ui::CPCWindow *ui;
    class CPCMeasureTab *m_measureTab;
    class CPCDiagnosticTab *m_diagnosticTab;
    class CPCToolsTab *m_toolsTab;
    class CPCHistogramTab *m_graphTab;
    class CPCPlusTab *m_plusTab;
    CUpdateManager *m_updateManager;

    void addTab(IPCTab *tab);
    bool canShowUpdatePopup() const;
};

#endif // CPCWINDOW_H
