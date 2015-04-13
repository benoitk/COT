#include "cotversion1.h"
#include "CVariableInt.h"
#include "CVariableVoie.h"
#include "CControlerAutomate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("COT");
    app.setApplicationVersion("1.1.0");

	CControlerAutomate controlerAutomate; //construit et execute l'automate

    COTVersion1 w;
	w.show();

    return app.exec();
}
