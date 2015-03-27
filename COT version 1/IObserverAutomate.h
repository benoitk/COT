#ifndef IOBSERVERAUTOMATE_H
#define IOBSERVERAUTOMATE_H

#include "CAutomate.h"

class IObserverAutomate 
{
public:

	// DEBUT Fenêtre principale 

	//desc : nouvelle ligne d'alarme 
	//entrées : identifiant(pour acquitement), date, heure et descriptif  
	virtual void updateAlarms(int, QDateTime, QString)=0; 
	
	//desc : Nouvelle ligne d'historique de mesure
	//entrées : date, heure, descriptif
	virtual void updateHistory(QDateTime, QString)=0; 
	
	//desc : Etat changé : En court, en pause, en arrêt
	//entrées : enum de l'état du cycle en cours
	virtual void updateStateCycle(CAutomate::eStateCycle)=0; 
	
	
	//desc : Etat changé : En défaut, en cycle, en maintenance
	//entrées : enum de l'état de l'automate
	virtual void updateStateAutomoate(CAutomate::eStateAutomate)=0; 

	//desc : Pas en cours changé 
	//entrées : pas en cours; label du pas 
	virtual void updateCurrentStep(float, QString)=0; 

	//desc : Nombre total de pas changé 
	//entrées : Nombre de pas total
	virtual void updateCountStep(int); 

	//desc : Voie en court changé 
	//entrées : numéro, Label voie 
	virtual void updateCurrentStream(int, QString); 

	//desc : Nombre total de voie changée 
	//entrées : Nombre de voie total
	virtual void updateCountStream(int); 

	//desc : Statue de voie changée : Active, en défeau d'eau...
	//entrées : enum de l'état de la voie 
	virtual void updateStateStream(CAutomate::eStateStream); 

	//desc : Valeur des variables de mesures affichable sur l'écran principale  (JSon : champ "streams->variables->type = measure)
	//entrées : identifiant et valeur de la variable de mesure, 
	virtual void updateMeasureValues(int, QVariant); 
	
	//desc : Label et unité des variables de mesures affichable sur l'écran principale
	//entrées : identifiant, label et unité de la variable
	virtual void updateMeasureLabels(int, QString); 

	//FIN fenêtre principale


	
};

#endif // IOBSERVERAUTOMATE_H
