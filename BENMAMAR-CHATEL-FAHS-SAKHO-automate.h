#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <iostream>
#include <string>
#include <vector>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-etat.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"

class Automate
{	
	private:
	vector <int> etats_initiaux;       // etat initiaux 
    vector <int> etats_finaux;       // etat finaux
    vector <string> alphabet;        // Alphabet lu
    vector <Transition> table_transition;  // tableau de structure des transitions de l'automate complet.
    vector <Etat> liste_etat;
    void AfficherAutomateMinimal(vector <vector <int> > state);

	public:
	bool LireFichier(string nom_fichier);
	void AfficherAutomate(int etat, string nom_fichier);
	bool EstDeterministe();
	bool EstAsynchrone();
	bool EstStandard();
	bool EstComplet();
	int getNombreCaracteresAlphabet();
	void Standardisation();
	bool Completion(bool poubelle);
	void Determinisation();
	void Minimisation();
	int getNombreEtats();
	int getNombreTransitions();
	void DecalageListeEtats();
	void DecalageListeTransitions();
	void LireMot(int option);
};

void Pause();

#endif