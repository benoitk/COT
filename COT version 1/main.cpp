#include "cotversion1.h"
#include "CInt.h"
#include "CVoie.h"
#include "CControlerAutomate.h"
#include <QtWidgets/QApplication>
#include <qdebug.h>


int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	COTversion1 w;
	CVoie* voie1 = new CVoie(&w);
	CInt* iTest = new CInt(voie1);
	qDebug() << "Voie 1" << voie1->children().count();
	CVoie* voie2 = new CVoie(&w);
	iTest->setParent(voie2);
	qDebug() << "Voie 1" << voie1->children().count();
	qDebug() << "Voie 2" << voie2->children().count();
	CControlerAutomate controlerAutomate; //construit et execute l'automate

	iTest->toString();
	w.show();
	return a.exec();
}
