#include "cotversion1.h"
#include "CVariableInt.h"
#include "CVariableVoie.h"
#include "CControlerAutomate.h"
#include <QtWidgets/QApplication>
#include <qdebug.h>


int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	COTversion1 w;
	CControlerAutomate controlerAutomate; //construit et execute l'automate

	w.show();
	return a.exec();
}
