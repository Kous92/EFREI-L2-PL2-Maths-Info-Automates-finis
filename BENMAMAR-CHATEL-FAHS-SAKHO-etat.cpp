#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-etat.h"

using namespace std;

// Constructeur
Etat::Etat(int nombre, bool debut, bool fin) 
{
	this->nombre = nombre;
	this->debut = debut;
	this->fin = fin;
    liste_etat_actuel.push_back(nombre);
}

Etat::Etat() 
{
	debut = false;
	fin = false;
}

int Etat::getEtat() 
{
	return nombre;
}

int Etat::getDebut()
{
	return debut;
}

int Etat::getFin()
{
	return fin;
}

// Mutateurs
void Etat::modifierEtat(int Nombre)
{
	nombre = Nombre;
}

void Etat::modifierEtatInitial(bool Debut)
{
	debut = Debut;
}

void Etat::modifierEtatFinal(bool Fin)
{
	fin = Fin;
}

bool TriVector(const Etat& E1, const Etat& E2)
{
	return E1.liste_etat_actuel[0] < E2.liste_etat_actuel[0];
}

bool TriTransition(const Transition& T1, const Transition& T2) 
{
  return T1.lien < T2.lien;
}

void SuppressionDoublonEtat(vector <Etat>& doublon) 
{
	for (int i = 0; i < doublon.size(); i++) 
	{
    	for (int j = 0; j < doublon.size(); j++) 
    	{
      		if ((i != j) && (doublon[i].getEtat() == doublon[j].getEtat()))
      		{
        		doublon.erase(doublon.begin() + i);
      		}
    	}
  	}
}

void SuppressionDoublonTransition(vector <Transition>& doublon) 
{
	for (int i = 0; i < doublon.size(); i++) 
	{
    	for (int j = 0; j < doublon.size(); j++) 
    	{
      		if ((i != j) && (doublon[i].lien == doublon[j].lien) && (doublon[i].fin == doublon[j].fin) && (doublon[i].debut == doublon[j].debut)) 
      		{
        		doublon.erase(doublon.begin() + i);
      		}
   		}
  	}
}

void SuppressionDoublonLettre(vector <string>& doublon)
{
    for (int i = 0; i < doublon.size(); i++) 
    {
        for (int j = 0; j < doublon.size(); j++) 
        {
            if (i != j && doublon[i] == doublon[j]) 
            {
                doublon.erase(doublon.begin() + i);
            }
        }
    }
}

void SuppressionDoublonCible(vector <int>& doublon)
{
    for (int i = 0; i < doublon.size(); i++) 
    {
        for (int j = 0; j < doublon.size(); j++) 
        {
            if (i != j && doublon[i] == doublon[j]) 
            {
                doublon.erase(doublon.begin() + i);
            }
        }
    }
}

void ReinitialiserEtat(Etat& E)
{
    E.modifierEtat(E.getEtat() + 1);  // Incrémente l'etat.
    E.modifierEtatFinal(false);
    E.modifierEtatInitial(false);
    E.liste_etat_actuel.clear();
    E.transition_etat.clear();
}

bool ComparerEtat(Etat& E, vector <Etat>& V, int& etat_trouve)
{    // return true si on le trouve

    // Comparaison plus rapide si les états sont dans l'ordre
    int m = 0;

    // Pour chaque état du vecteur 
    for (int i = 0; i < V.size(); i++) 
    {
        if (V[i].liste_etat_actuel.size() == E.liste_etat_actuel.size()) 
        {
            // pour chaque état de l'état
            for (int j = 0; j < E.liste_etat_actuel.size(); j++) 
            {
                // Pour chaque état de l'état du vecteur
                for (int k = 0; k < V[i].liste_etat_actuel.size(); k++) 
                {
                    if (E.liste_etat_actuel[j] == V[i].liste_etat_actuel[k]) 
                    {
                        m++;
                    }
                }
            }
            
            // Si on a trouvé l'état
            if (m == E.liste_etat_actuel.size()) 
            {
                etat_trouve = V[i].getEtat();
                return true;
            } 
            else 
            {
                m = 0;
            }
        }
    }

  // Si on n'a pas trouvé l'etat
  return false;

}

string intToGroupe(int temporaire)
{
  string romain;

  switch (temporaire) 
  {
    case 1:
    romain = "T";
    break;
    
    case 2:
    romain = "NT";
    break;
    
    case 3:
    romain = "A";
    break;
    
    case 4:
    romain = "B";
    break;
    
    case 5:
    romain = "C";
    break;
    
    case 6:
    romain = "D";
    break;
    
    case 7:
    romain = "E";
    break;
    
    case 8:
    romain = "F";
    break;
    
    case 9:
    romain = "G";
    break;
    
    case 10:
    romain = "H";
    break;
    
    case 11:
    romain = "I";
    break;
    
    case 12:
    romain = "J";
    break;
  }

  return romain;
}
