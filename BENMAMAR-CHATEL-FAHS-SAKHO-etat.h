#ifndef ETAT_H
#define ETAT_H

#include <string>
#include <iostream>
#include <vector>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"

using namespace std;

class Etat
{			
	private:
	bool debut;
	bool fin;
	int nombre;

	public:
	vector <Transition> transition_etat;
	vector <int> liste_etat_actuel;

	Etat(int nombre, bool debut, bool fin);
	Etat();

	// Accesseurs
	int getEtat(); 
	int getDebut();
	int getFin();
	int getNombreEtats();

	// Mutateurs
	void modifierEtat(int Nombre);
	void modifierEtatInitial(bool Debut);
	void modifierEtatFinal(bool Fin); 
};

bool TriVector(const Etat& E1, const Etat& E2);
bool TriTransition(const Transition& T1, const Transition& T2);
void SuppressionDoublonEtat(vector <Etat>& doublon);
void SuppressionDoublonTransition(vector <Transition>& doublon);
void SuppressionDoublonLettre(vector <string>& doublon); 
void SuppressionDoublonCible(vector <int>& doublon); 
void ReinitialiserEtat(Etat& E);
bool ComparerEtat(Etat& E, vector <Etat>& V, int& etat_trouve);
string intToGroupe(int temporaire);

#endif