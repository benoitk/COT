#include "CAboutWindow.h"
#include "CToolButton.h"
#include "CVerticalButtonBar.h"

#include <QLabel>
#include <QAction>
#include <QApplication>

// KDAB_TODO: Fix me
#define NUM_VERSION_5 "N/C"

CAboutWindow::CAboutWindow(QWidget *parent)
    : CDialog(parent)
{
    setTitle(tr("INFORMATION"));
    QLabel *lInformations = new QLabel(this);
    lInformations->setText(tr("%1 (%2)\n\nGUI version:\n%3\n%4\nSupervision version:\n%5")
                               .arg(qApp->applicationDisplayName())
                               .arg(qApp->applicationName())
                               .arg(qApp->applicationVersion())
                               .arg(analyzerString())
                               .arg(NUM_VERSION_5));
    setMainWidget(lInformations);

    connect(buttonBar()->addAction(CToolButton::Ok), &QAction::triggered, this, &CAboutWindow::close);
}

CAboutWindow::~CAboutWindow()
{
}

QString CAboutWindow::analyzerString() const
{
    QString typeAnalyseur;
#ifdef SONDE
    typeAnalyseur = "SONDE";
#elif defined(KMNO4)
    typeAnalyseur = "KMNO4";
#elif defined(TITRI)
    typeAnalyseur = "TITRI";
#elif defined(SILICE)
    typeAnalyseur = "SILICE";
#elif defined(COULEUR)
    typeAnalyseur = "COULEUR";
#elif defined(COLO)
    typeAnalyseur = "COLO";
#endif

#if defined(CALIBRATIONS_INDEPENDANTE)
    typeAnalyseur = "\nCALIBRATION INDEPENDANTE DES VOIES\n" + typeAnalyseur;
#endif
#if defined(MULTI_STREAM)
    typeAnalyseur = "MULTI STREAM " + typeAnalyseur;
#endif

#if defined(MULTI_MEASURE)
    typeAnalyseur = "MULTI MEASURE " + typeAnalyseur;
#endif

#if defined(PH)
    typeAnalyseur = "PH " + typeAnalyseur;
#endif

#if defined(CHROME)
    typeAnalyseur = "CHROME " + typeAnalyseur;
#endif

#ifdef MULTI_EV
    typeAnalyseur = "\nMulti EV " + typeAnalyseur;
#endif

#ifdef SULFITE
    typeAnalyseur = "SULFITE " + typeAnalyseur;
#endif
#ifdef CERIUM
    typeAnalyseur = "CERIUM " + typeAnalyseur;
#endif
#if defined(MAGNESIUM)
    typeAnalyseur = "MAGNESIUM " + typeAnalyseur;
#endif
#if defined(CALCIUM_MAGNESIUM)
    typeAnalyseur = "Ca+Mg " + typeAnalyseur;
#endif

#if defined(SELECTEUR)
    typeAnalyseur = typeAnalyseur +tr(" avec SELECTEUR");
#endif

#if defined(R_D)
    typeAnalyseur = typeAnalyseur + "\nVERSION R&D";
#endif

    return typeAnalyseur;
}
