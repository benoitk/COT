#include "cotversion1.h"
#include "CVariableInt.h"
#include "CVariableVoie.h"
#include "CControlerAutomate.h"
#include "CTranslationGenerator.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);

	CControlerAutomate controlerAutomate; //construit et execute l'automate

    CTranslationGenerator trGenerator;
    const QString qmOutput = QStringLiteral("%1/%2translations/")
            .arg(QApplication::applicationDirPath())
            .arg(
#if defined(Q_OS_MACX)
                QStringLiteral("/../Resources/")
#else
                QString()
#endif
                )
    ;
    if (!trGenerator.generateFrom(QString::fromUtf8(COT_JSON_FILE), qmOutput)) {
        qDebug("%s: Can't generate translations (%s).", Q_FUNC_INFO, qPrintable(qmOutput));
    }

    COTversion1 w;
	w.show();

	return a.exec();
}
