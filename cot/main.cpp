#include "cotversion1.h"
#include "CVariableInt.h"
#include "CVariableVoie.h"
#include "CControlerAutomate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);

	CControlerAutomate controlerAutomate; //construit et execute l'automate

    COTVersion1 w;
	w.show();

	return a.exec();
}
