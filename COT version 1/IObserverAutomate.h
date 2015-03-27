#ifndef IOBSERVERAUTOMATE_H
#define IOBSERVERAUTOMATE_H

#include "CAutomate.h"

class IObserverAutomate 
{
public:

	// DEBUT Fen�tre principale 

	//desc : nouvelle ligne d'alarme 
	//entr�es : identifiant(pour acquitement), date, heure et descriptif  
	virtual void updateAlarms(int, QDateTime, QString)=0; 
	
	//desc : Nouvelle ligne d'historique de mesure
	//entr�es : date, heure, descriptif
	virtual void updateHistory(QDateTime, QString)=0; 
	
	//desc : Etat chang� : En court, en pause, en arr�t
	//entr�es : enum de l'�tat du cycle en cours
	virtual void updateStateCycle(CAutomate::eStateCycle)=0; 
	
	
	//desc : Etat chang� : En d�faut, en cycle, en maintenance
	//entr�es : enum de l'�tat de l'automate
	virtual void updateStateAutomoate(CAutomate::eStateAutomate)=0; 

	//desc : Pas en cours chang� 
	//entr�es : pas en cours; label du pas 
	virtual void updateCurrentStep(float, QString)=0; 

	//desc : Nombre total de pas chang� 
	//entr�es : Nombre de pas total
	virtual void updateCountStep(int); 

	//desc : Voie en court chang� 
	//entr�es : num�ro, Label voie 
	virtual void updateCurrentStream(int, QString); 

	//desc : Nombre total de voie chang�e 
	//entr�es : Nombre de voie total
	virtual void updateCountStream(int); 

	//desc : Statue de voie chang�e : Active, en d�feau d'eau...
	//entr�es : enum de l'�tat de la voie 
	virtual void updateStateStream(CAutomate::eStateStream); 

	//desc : Valeur des variables de mesures affichable sur l'�cran principale  (JSon : champ "streams->variables->type = measure)
	//entr�es : identifiant et valeur de la variable de mesure, 
	virtual void updateMeasureValues(int, QVariant); 
	
	//desc : Label et unit� des variables de mesures affichable sur l'�cran principale
	//entr�es : identifiant, label et unit� de la variable
	virtual void updateMeasureLabels(int, QString); 

	//FIN fen�tre principale


	
};

#endif // IOBSERVERAUTOMATE_H
