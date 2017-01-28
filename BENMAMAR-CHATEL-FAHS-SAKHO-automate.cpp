#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-automate.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-etat.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-menu.h"

using namespace std;

bool Automate::LireFichier(string nom_fichier) 
{
	system("clear");

    string temporaire;
	bool valide = true; // Booléen de contrôle de chargement de l'automate (validation)        
	unsigned int i = 0, j = 0; // Variables itératrices pour les boucles for

	// Lors de chaque recharge d'automate, il est recommandé de nettoyer tous les tableaux dynamiques (vectors) de l'objet
	etats_initiaux.clear();
	etats_finaux.clear();
	alphabet.clear();
	table_transition.clear();
	liste_etat.clear();

	// Type ifstream: ouverture de fichier (Ici: fichier de vérification des mots-clés)
	ifstream VerificationFichier;           

	cout << ">>> Ouverture du fichier " << nom_fichier << "..." << endl << endl;

	VerificationFichier.open(nom_fichier.c_str()); // Ouverture du fichier

	if (VerificationFichier) // Le fichier existe
  	{
		wcout << L"Le fichier existe: chargement des données..." << endl;
		VerificationFichier >> temporaire;

    	if (temporaire != "EtatInitiaux") 
    	{
    		wcout << L"État initial détecté..." << endl;
    		VerificationFichier.close(); // Erreur de lecture: fermeture du fichier car l'état initial est inexistant
    		return false;
    	}

    	if (valide == true) 
    	{
      		valide = false;

      		// Tant qu'on a pas trouvé le mot-clé dans le fichier (ici EtatFinaux)
      		while(!((valide == true) || (VerificationFichier.eof()))) 
      		{   
        		VerificationFichier >> temporaire;

        		if (temporaire == "EtatFinaux") 
        		{
          			wcout << L"État final détecté..." << endl;
          			valide = true;
        		}
      		}
    	}

    	if (valide) 
    	{
      		valide = false;

      		// Tant qu'on a pas trouvé le mot-clé dans le fichier (ici EtatFinaux)
      		while (!((valide == true) || (VerificationFichier.eof())))
      		{
        		VerificationFichier >> temporaire;

        		if (temporaire == "Alphabet") 
        		{
          			wcout << L"Alphabet détecté..." << endl;
          			valide = true;
        		}
      		}
    	}

    	if (valide == true)
    	{
      		valide = false;

      		while (!((valide == true) || (VerificationFichier.eof()))) 
      		{
        		VerificationFichier >> temporaire;

        		if (temporaire == "Automate") 
        		{
          			wcout << L"Automate détecté..." << endl;
          			valide = true;
        		}
      		}
    	}

	    if (valide == true) 
	    {
	    	valide = false;

	    	while (!((valide == true) || (VerificationFichier.eof()))) 
	    	{
	        	VerificationFichier >> temporaire;

	        	if (temporaire == "FIN") 
	        	{
	          		wcout << L"FIN détecté..." << endl;
	          		valide = true;
	        	}
	      	}
	    }

	    wcout << L">>> Le fichier est valide..." << endl << endl;

	    VerificationFichier.close(); // Fermeture du fichier: fin de la vérification des mots-clés

	    if (!valide) 
	    {
	    	return false;
	    }
	} 
	else 
	{
	    wcerr << L"Erreur à l'ouverture du fichier !" << endl;

	    return false;
	}

  	ifstream Fichier;

  	Fichier.open(nom_fichier.c_str());

  	if (Fichier) // Fichier existant
  	{
	    // On elimine la première ligne        
	    Fichier >> temporaire;

	    wcout << L"Récuperation des états de l'automate..." << endl << endl;
	    // Recupéreration des états initiaux
	    Fichier >> temporaire;

	    if (temporaire == "EtatInitiaux") 
	    {
	    	wcerr << L"Erreur: L'automate n'a pas d'état initial. Veuillez choisir un fichier valide !" << endl;
	      	Fichier.close();
	      	return false;
	    }

	    while (temporaire != "EtatFinaux") 
	    {
	    	wcout << L">>> Récuperation des états initiaux de l'automate..." << endl;
	    	etats_initiaux.push_back(atoi(temporaire.c_str()));
	      	Fichier >> temporaire;
	    }

	    // Récuperation des états finaux
	    Fichier >> temporaire;

	    while (temporaire != "Alphabet") 
	    {
	    	wcout << L">>> Récuperation des états finaux de l'automate..." << endl;
	    	etats_finaux.push_back(atoi(temporaire.c_str()));
	      	Fichier >> temporaire;
	    }

	    // Récupération de l'alphabet
	    Fichier >> temporaire;

	    while (temporaire != "Automate") 
	    {
		    alphabet.push_back(temporaire);
		    
		    wcout << L">>> Récuperation de l'alphabet de l'automate... (caractère ";
		    cout << temporaire << ")" << endl;

		    Fichier >> temporaire;
	    }

	    i = 0;
	    j = 0;

	    bool trouve = false, start, end, lecture = false;
	    int etat_temporaire;               // stock l'etat sous forme d'entier pour eviter de rappeler atoi en boucle
	    string temporaire1; // La premiere étape de la transition est gardé en mémoire
	    string temporaire2; // La deuxième étape de la transition

	    wcout << L">>> Récuperation des transitions de l'automate..." << endl;

    	while(temporaire != "FIN") 
    	{
	    	if (temporaire == "FIN" || !lecture) 
	    	{
	    		Fichier >> temporaire;
	        	lecture = true;
	      	}
	     	
	     	// À chaque état rencontré, on verifie qu'il existe, sinon on le crée et on trie le tableau
	      	if (((i % 3) != 1)) 
	      	{      
				// Tous les cas sauf l'alphabet de transition 
	        	trouve = false;
	        	etat_temporaire = atoi(temporaire.c_str());

	        	if (liste_etat.size() != 0) 
	        	{  
	        	    // Condition ne servant probablement à rien dans la version actuelle du code
	        		for (j = 0; j < liste_etat.size(); j++) 
	        		{
	            		if (liste_etat[j].getEtat() == etat_temporaire) 
	            		{     
	              			trouve = true; // État existant
	            		}
	          		}
	        	}

	        	// État inexistant
		        if (liste_etat.size() == 0 || trouve == false)
		        { 

		          	// rechercher ses attribus init / final 
		          	start = end = false;
		          	
		          	for (j = 0; j < etats_initiaux.size() && !start; j++) 
		          	{
		            	if (etats_initiaux[j] == etat_temporaire) 
		            	{
		              		start = true;
		            	}
		          	}
		          	
		          	for (j = 0; j < etats_finaux.size() && !end; j++) 
		          	{
		          	  	if (etats_finaux[j] == etat_temporaire) 
		          	  	{
		            		end = true;
		            	}
		          	}
		          	
		          	// Création de l'etat
		          	liste_etat.push_back(Etat(etat_temporaire, start, end));
		        }
	      	}	

		    if ((i % 3) == 0) 
		    {   
		    	// départ de la transition
		    	temporaire1 = temporaire;
		    }

		    trouve = false;

		    if ((i % 3) == 1)
		    {        
		    	// Alphabet utilisé 
		        for (j = 0; j < alphabet.size(); j++) 
		        {
		        	// Si la lettre est dans l'alphabet
		        	if (alphabet[j] == temporaire) 
		         	{    
		            	trouve = true;
		        	}
		    	}

		        // Si l'a lettre n'a pas été trouvée
		        if (!trouve) 
		        {
		       		wcerr << L"La lettre de transition n'a pas été trouvée dans l'alphabet" << endl;
		        	Fichier.close();

		        	return false;
		        }

        		temporaire2 = temporaire;
      		}
      		
      		if ((i % 3) == 2) 
      		{         
        		// On rajoute la transition dans l'automate et son état
        		table_transition.push_back(Transition(atoi(temporaire1.c_str()), temporaire2, atoi(temporaire.c_str())));

        		for (j = 0; j < liste_etat.size(); j++) 
        		{
          			if (liste_etat[j].getEtat() == atoi(temporaire1.c_str())) 
          			{
            			// Initialisation de la structure transition au sein du tableau dynamique (vector) de transition de la classe Etat
            			liste_etat[j].transition_etat.push_back(Transition(atoi(temporaire1.c_str()), temporaire2, atoi(temporaire.c_str())));
          			}
        		}
     		}

      		Fichier >> temporaire;
      		i++;
   		}

   		wcout << L">>> Lecture de l'automate terminée" << endl << endl;
    	Fichier.close();       // Toutes bonne chose à une fin
  	} 
  	else 
  	{
  		wcerr << L"Erreur à l'ouverture !" << endl;
    	return false;
  	}

  	// On trie la liste des états de l'automate dans l'ordre croissant pour que l'affichage soit plus plus beau.     
  	sort(liste_etat.begin(), liste_etat.end(), TriVector);

  	if (liste_etat.size() == 1) 
  	{
    	liste_etat[0].modifierEtat(1);
  	}

	return true;  // si tout a été chargé normalement
}

void Automate::AfficherAutomate(int etat, string nom_fichier) 
{
	// Affichage de l'automate chargé
  	wcout << endl << L">>> Affichage de l'automate chargé: ";
  	cout << nom_fichier << endl << endl;

  	bool trouveDebut = false, trouveFin = false, trouveAffiche = false;
  	int i = 0;

  	cout << "*****************************************************" << endl;
  	cout << "*****     Table de transitions de l'automate    *****" << endl;
  	cout << "*****************************************************" << endl << endl;

  	if (etat >= 3) 
  	{
    	cout << "|  E/S   |" << "    Etat    |   ";
  	} 
  	else 
  	{
    	cout << "|  E/S   |" << "  Etat  |   ";      //<<
  	}

  	for (i = 0; i < alphabet.size(); i++) 
  	{
  		cout << alphabet[i] << "   |   ";
  	}

  	if (etat >= 3) 
  	{
    	cout << endl << "----------------------";
  	} 
  	else 
  	{
    	cout << endl << "------------------";
  	}


  	for (int j = 0; j < alphabet.size(); j++) 
  	{
    	cout << "--------";
  	}
  	
  	cout << endl;

  	for (i = 0; i < liste_etat.size(); i++) 
  	{
    	trouveDebut = trouveFin = false;

    	for (int j = 0; j < etats_initiaux.size(); j++) 
    	{
     		if (etats_initiaux[j] == liste_etat[i].getEtat()) 
     		{
        		trouveDebut = true;
      		}
    	}

    	for (int j = 0; j < etats_finaux.size(); j++) 
    	{
     		if (etats_finaux[j] == liste_etat[i].getEtat()) 
     		{
        		trouveFin = true;
      		}
    	}

	    if (trouveDebut) 
	    {
	    	if (trouveFin) 
	    	{    
	    		// L'état de l'automate est initial et terminal
	        	cout << "|  <-->";
	      	} 
	      	else 
	      	{   
	      		// L'état de l'automate est initial
	        	cout << "|  --> ";
	      	}
	    } 
	    else 
	    {
	    	if (trouveFin) 
	    	{   
	    		// L'état de l'automate est terminal
	        	cout << "|  <-- ";
	      	} 
	      	else 
	      	{   
	      		// L'état de l'automate est ni terminal, ni initial
	        	cout << "|      ";
	      	}
	    }

    	cout << "  | ";

	    /* Affichage des états:
	       * On tient compte du nombre d'états (jusqu'à 99) 
	       * Affichage des numéros d'etats
	    */

    	if (etat >= 3) 
    	{
    		if (liste_etat[i].getEtat() > 9) 
    	  	{
        		cout << "" << liste_etat[i].getEtat() << ": ";

        		for (int j = 0; j < liste_etat[i].liste_etat_actuel.size(); j++) 
        		{
          			cout << liste_etat[i].liste_etat_actuel[j] << " ";
        		}

		        for (int j = (liste_etat[i].liste_etat_actuel.size() * 2); j < 7; j++) 
		        {
		          	cout << " ";
		        }
      		} 
      		else if (etat == 4 && liste_etat[i].getEtat() == liste_etat[liste_etat.size() - 1].getEtat()) 
      		{
        		cout << " " << "    P   " << "  |";
     		} 
     		else 
     		{
        		cout << "" << liste_etat[i].getEtat() << ": ";

        		for (int j = 0; j < liste_etat[i].liste_etat_actuel.size(); j++) 
        		{
          			cout << liste_etat[i].liste_etat_actuel[j] << " ";
        		}
        		
        		for (int j = (liste_etat[i].liste_etat_actuel.size() * 2); j < 8; j++) 
        		{
          			cout << " ";
        		}
        		
        		cout << "|";
      		}
    	} 
    	else 
    	{
      		if (liste_etat[i].getEtat() > 9) 
      		{
        		cout << "  " << liste_etat[i].getEtat() << "   |";
      		} 
      		else if (etat == 4 && liste_etat[i].getEtat() == liste_etat[liste_etat.size() - 1].getEtat()) 
      		{
        		cout << " " << " P  " << "  |";
      		} 
      		else 
      		{
        		cout << "   " << liste_etat[i].getEtat() << "   |";
      		}
    	}

    	vector <int> affichage;

    	// Affichage des transitions
    	for (int j = 0; j < alphabet.size(); j++) 
    	{
     		for (int k = 0; k < liste_etat[i].transition_etat.size(); k++) 
     		{
        		if (liste_etat[i].transition_etat[k].lien == alphabet[j]) 
        		{
          			trouveAffiche = true;
          			affichage.push_back(liste_etat[i].transition_etat[k].fin);
        		}
      		}

      		if (trouveAffiche) 
      		{
        		// Affichage des états poubelle si l'automate fini est déterministe et complet
        		if (etat == 4 && affichage[0] == liste_etat[liste_etat.size() - 1].getEtat()) 
        		{
          			cout << " " << " P  " << "  |";
        		} 
        		else 
        		{
          			if (etat == 2) 
          			{
            			for (int k = 0; k < affichage.size(); k++) 
            			{
              				if (affichage.size() == 1) 
              				{
                				cout << "   " << affichage[i] << "   ";
	              			} 
	              			else if (affichage.size() == 2) 
	              			{
	                			cout << " " << affichage[i] << " ";
	              			} 
	              			else 
	              			{  // l'affichage sera un peu déformer
	                			cout << "" << affichage[i] << " ";
	              			}
		            	}

		            	if (affichage.size() == 1) 
		            	{
		              		cout << "|";
		            	} 
		            	else if (affichage.size() == 2) 
		            	{
		              		cout << " |";
		            	} 
		            	else 
		            	{    // l'affichage sera un peu déformer
		              		cout << "|";
		            	}
          			} 
         			else 
         			{
            			cout << "   " << affichage[0] << "   |";
          			}
       			}
      		} 
      		else 
      		{
        		cout << "       |";
      		}

      		trouveAffiche = false;
      		affichage.clear(); // Nettoyage du tableau dynamique d'affichage

      /*# pour chaque lettre 
		 si la transition lié a la lettre existe
		 	on affiche l'etat final 
		 sinon 
		 	on affiche un blanc
		 fin si
         fin pour 
       */
    	}

	    if (etat >= 3) 
	    {
	    	cout << endl << "----------------------";
	    } 
	    else 
	    {
	    	cout << endl << "------------------";
	    }
	    
	    for (int j = 0; j < alphabet.size(); j++) 
	    {
	    	cout << "--------";
	    }
	    
	    cout << endl;
  	}

  	cout << endl;
}

bool Automate::EstDeterministe() 
{
	/* Un automate est déterministe si et seulement si:
	   - Il n'a qu'un seul état initial (une seule entrée)
	   - Chaque état doit faire transiter une seule fois un caractère précis dans ses transitions
	*/

	// Si l'automate a plus d'un état initial, il n'est pas déterministe
  	if (etats_initiaux.size() > 1) 
	{
  		return false;       
  	}

  	/* Vérification des transitions: chaque transition d'un état ne doit faire transiter qu'une seule fois le caractère
  	   * On fait une triple imbrication de boucles for afin que dans la liste d'états on vérifie qu'une transition
  	   - 1ère boucle: on itère dans la liste des états de l'automate
  	   - 2ème boucle: En entrant dans la liste d'état, on va itérer afin d'analyser les transitions de l'état avec j
  	   - 3ème boucle: Pareil que la 2ème boucle, mais avec k, comme itérateur
  	   - Dans la 3ème boucle on vérifie dans les transitions de 2 états différents que les caractères (lien) dans la transition ne soient pas
  	     les mêmes (pour 2 états différents, on s'assure que j != k)
  	*/
  	for (int i = 0; i < liste_etat.size(); i++) 
  	{
    	for (int j = 0; j < liste_etat[i].transition_etat.size(); j++) 
    	{
     		for (int k = 0; k < liste_etat[i].transition_etat.size(); k++) 
      		{        
      			// Avec (k = j) à verifier, pour savoir si les transitions d'un état ne contiennent qu'une seule fois le caractère
        		if ((liste_etat[i].transition_etat[j].lien == liste_etat[i].transition_etat[k].lien) && (k != j)) 
        		{
          			// Si il y a deux fois la meme lettre dans les transitions d'un etat, l'automate n'est pas déterministe
          			return false;
        		}
      		}
    	}
  	}
  	
  	// Si tout l'automate a été parcouru sans interruption, alors il est déterministe
  	return true;
}

bool Automate::EstAsynchrone()
{
	/* Un automate est asynchrone si et seulement si il reconnait le mot vide:
	   - Au moins une de ses transitions contient le mot vide (epsilon = '*')
	*/
	for (int i = 0; i < liste_etat.size(); i++) 
  	{
    	for (int j = 0; j < liste_etat[i].transition_etat.size(); j++) 
    	{
        	if (liste_etat[i].transition_etat[j].lien == "*") 
        	{
          		// Si au moins une transition contient le mot vide, l'automate est asynchrone
          		return true;
        	}
      	}
    }

    // L'automate est synchrone et ne contient pas de mot vide
	return false;
}

bool Automate::EstStandard()
{
    bool standard = true; // Automate standard ou non (vérification)

	/* Un automate est standard si et seulement si:
	   - Il n'a qu'un seul état initial (une seule entrée)
	   - L'état initial ne doit pas être la cible d'une transition d'un autre état
	*/

	// Si l'automate a plus d'un état initial, il n'est pas standard
  	if (etats_initiaux.size() > 1) 
	{
  		standard = false;       
  	}
  	else
  	{
  		for (int i = 0; i < table_transition.size() && standard; i++)
  		{
  			if (etats_initiaux[0] == table_transition[i].fin)
  			{
  				standard = false;
  			}
  		}
  	}

  	if (liste_etat.size() == 1)
  	{
  		standard = true;
  	}

  	return standard;
}

bool Automate::EstComplet()
{
    bool complet = true; // Automate complet ou non (vérification)

    /* Un automate est complet si et seulement si:
       - L'automate a toutes ses transitions
       - Le nombre de transitions est égal au produit du nombre de caractères de l'alphabet et du nombre d'états
    */

    // Si l'automate n'a pas toutes ses transitions.
    if (getNombreTransitions() < (getNombreEtats() * getNombreCaracteresAlphabet()))
    {
        complet = false;
    }
        
    return complet;
}

void Automate::Standardisation()
{
	
    cout << ">>> Standardisation de l'automate..." << endl << endl;
    cout << "Etats: " << getNombreEtats() << ", transitions: " << getNombreTransitions() << endl << endl;

    Etat EtatTemporaire(0, true, false); // Futur état initial (état i)

    for (unsigned int i = 0; i < etats_initiaux.size(); i++) 
    {
    	// Si il est initial et final on le rajoute à la liste des état finaux
      	for (unsigned int j = 0; j < etats_finaux.size() && etats_initiaux[i] == etats_finaux[j]; j++) 
      	{
        	wcout << L" * L'état: " << etats_initiaux[i] << " devient un état final." << endl;
            EtatTemporaire.modifierEtatFinal(true);
        	etats_finaux.push_back(0);
            wcout << L" * Nouvel état initial: " << etats_finaux[j] << endl;
      	}

      	for (unsigned int j = 0; j < liste_etat.size(); j++) 
      	{
        	// Si l'etat est initial et que l'on est dans la table de transition.
        	// On rajoute la transition dans l'etat temporaire
        	for (unsigned int k = 0; (k < liste_etat[j].transition_etat.size()) && (liste_etat[j].getEtat() == etats_initiaux[i]); k++) 
            {
                cout << " * Nouvelle transition: " << liste_etat[j].getEtat() << " " << liste_etat[j].transition_etat[k].lien << " " << liste_etat[j].getFin() << endl;
                EtatTemporaire.transition_etat.push_back(liste_etat[j].transition_etat[k]);
        	}
        	
        	liste_etat[j].modifierEtatInitial(false); // On enleve tout les etat initiaux de l'automate
      	}
    }

    etats_initiaux.clear();

    // On supprime les potentiels doublons
    for (int i = 0; i < EtatTemporaire.transition_etat.size(); i++) 
    {
    	EtatTemporaire.transition_etat[i].debut = 0;    // On considère 0 comme initial
      	table_transition.push_back(EtatTemporaire.transition_etat[i]);
    }

    SuppressionDoublonTransition(EtatTemporaire.transition_etat);

    etats_initiaux.push_back(0);    // Mise à jour de la table des états initiaux
    liste_etat.push_back(EtatTemporaire);
    SuppressionDoublonEtat(liste_etat);
    sort(liste_etat.begin(), liste_etat.end(), TriVector); // Un peu de rangements ...

    wcout << L">>> Automate standardisé" << endl << endl;
}

bool Automate::Completion(bool poubelle)
{
    // Automate déjà complet: détection de l'état poubelle
    if (poubelle)
    {
        wcout << L">>> Vérification de l'état poubelle..." << endl;
    }
    else
    {
         wcout << L">>> Complétion de l'automate..." << endl << endl;
    }

    wcout << L"États: " << getNombreEtats() << endl;
    cout << "Transitions: " << getNombreTransitions() << " / " << (getNombreEtats() * getNombreCaracteresAlphabet()) << endl << endl;

    // Pour l'état poubelle
    int poussiere_trouvee = 0;
    bool poussiere = true;

    // Recherche: si un état est déjà une poubelle
    for (int i = 0; i < liste_etat.size() && poussiere; i++) 
    {
        poussiere = true;

        if (liste_etat[i].transition_etat.size() == 0) 
        {
            poussiere_trouvee = i;     // Si il l'etat n'a pas de transition.
        } 
        else 
        {
            poussiere_trouvee = i;
            
            for (int j = 0; j < liste_etat[i].transition_etat.size() && poussiere_trouvee; j++) 
            {
                poussiere_trouvee = i;
                
                if (liste_etat[i].transition_etat[j].fin != liste_etat[i].getEtat()) 
                {
                    poussiere_trouvee = 0; // Si un etat n'a pas de transition autre que sur lui-même.
                }
            }
        
            if (poussiere_trouvee) 
            {
                poussiere = false;
            }
        }
        
        // Si on a trouvé un état poubelle, on vérifie qu'il n'est pas final
        if (poussiere_trouvee) 
        {
            for (int k = 0; k < etats_finaux.size(); k++) 
            {
                if (liste_etat[i].getEtat() == etats_finaux[k]) 
                {
                    poussiere_trouvee = 0;
                    poussiere = true;
                }
            }
        }
    }

    // Création état poubelle
    Etat Poubelle(liste_etat.size() + 1, false, false);

    // Si on en a pas encore trouvé d'état implicite
    if (!poussiere_trouvee) 
    {       
        // Si l'automate n'est pas encore complet
        if (!poubelle) 
        { 
            poussiere_trouvee = liste_etat.size();
            
            for (int i = 0; i < alphabet.size(); i++) 
            {
                // On met à jour les transitions de l'état poubelle (de lui-même vers lui-même)
                Poubelle.transition_etat.push_back(Transition(Poubelle.getEtat(), alphabet[i], Poubelle.getEtat()));
            }

            liste_etat.push_back(Etat(Poubelle));
            
            // On rajoute l'état au vecteur d'état
            for (int i = 0; i < Poubelle.transition_etat.size(); i++) 
            {
                table_transition.push_back(Transition(Poubelle.transition_etat[i]));  // On met à jour les transitions
            }
        }
    } 
    else 
    {
        Poubelle = liste_etat[poussiere_trouvee]; // On récupère l'état poubelle
        liste_etat.push_back(Etat(Poubelle)); // On le rajoute à la fin de la liste des états
        SuppressionDoublonEtat(liste_etat); // Supprimera la première occurence trouvée du double

        // On regarde si la transition existe
        for (int j = 0; j < alphabet.size(); j++) 
        {
            bool continuer = true;

            for (int i = 0; i < liste_etat[poussiere_trouvee].transition_etat.size() && continuer; i++) 
            {
                if (liste_etat[poussiere_trouvee].transition_etat[i].lien == alphabet[j]) 
                {
                    continuer = false;
                }
            }

            // Si nécessaire: on met à jour les tables de transitions
            if (continuer) 
            {
                liste_etat[poussiere_trouvee].transition_etat.push_back(Transition(liste_etat[poussiere_trouvee].getEtat(), alphabet[j], liste_etat[poussiere_trouvee].getEtat()));
                table_transition.push_back(Transition(liste_etat[poussiere_trouvee].getEtat(), alphabet[j], liste_etat[poussiere_trouvee].getEtat()));
            }

        }   
    }


    bool trouve = false;

    /* Complétion: algorithme
     Pour chaque case de la table de transition
         Si la transition n'existe pas
            On la rajoute au deux vectors de transition
         Fin Si
     Fin Pour table de transition
    */

    for (int i = 0; i < liste_etat.size(); i++) 
    {
        for (int j = 0; j < alphabet.size(); j++) 
        {
            for (int k = 0; k < liste_etat[i].transition_etat.size(); k++) 
            {
                if (alphabet[j] == liste_etat[i].transition_etat[k].lien) 
                {
                    trouve = true;
                }
            }

            if (!trouve) 
            {
                liste_etat[i].transition_etat.push_back(Transition(liste_etat[i].getEtat(), alphabet[j], liste_etat[poussiere_trouvee].getEtat()));
                table_transition.push_back(Transition(liste_etat[i].getEtat(), alphabet[j], liste_etat[poussiere_trouvee].getEtat()));
            }
            trouve = false;
        }

        // On trie la liste des transitions.
        sort(liste_etat[i].transition_etat.begin(), liste_etat[i].transition_etat.end(), TriTransition);
    }

    cout << endl;

    return !poussiere; // Si on n'a rien fait on l'indique
}

void Automate::Determinisation()
{
    wcout << L">>> Déterminisation de l'automate..." << endl;

    vector <Etat> VectorEtatTemporaire; // contient le futur vector d'etat de l'automate
    Etat EtatTemporaire;               // contient l'etat temporaire a ajouter au tableau d'etat. 

    // Création du premier état de l'automate deterministe
    EtatTemporaire.modifierEtat(1);
    EtatTemporaire.modifierEtatInitial(true); // Le premier état est forcément initial

    for (int i = 0; i < etats_initiaux.size(); i++) 
    {
        for (int j = 0; j < liste_etat.size(); j++) 
        {
            if (etats_initiaux[i] == liste_etat[j].getEtat()) 
            {
                EtatTemporaire.liste_etat_actuel.push_back(etats_initiaux[i]);
            }
        }
    }

    for (int i = 0; i < EtatTemporaire.liste_etat_actuel.size(); i++) 
    {
        for (int j = 0; j < etats_finaux.size() && EtatTemporaire.liste_etat_actuel[i] == etats_finaux[j]; j++) 
        {
            EtatTemporaire.modifierEtatFinal(true);
        }
    }
    
    VectorEtatTemporaire.push_back(Etat(EtatTemporaire));
    ReinitialiserEtat(EtatTemporaire);

    int iterateur = 0;

    // Tant qu'on a pas testé tous les états de VectorEtatTemporaire
    while (iterateur < VectorEtatTemporaire.size()) 
    {     
        // Récuperation de l'alphabet lu par l'état. On évite alors de devoir tester tous les états par la suite
        vector <string> lien_temporaire;

        for (int i = 0; i < VectorEtatTemporaire[iterateur].liste_etat_actuel.size(); i++) 
        {
            for (int j = 0; j < liste_etat.size(); j++) 
            {
                if (VectorEtatTemporaire[iterateur].liste_etat_actuel[i] == liste_etat[j].getEtat()) 
                {
                    for (int k = 0; k < liste_etat[j].transition_etat.size(); k++) 
                    {
                        lien_temporaire.push_back(liste_etat[j].transition_etat[k].lien);
                    }
                }
            }
        }

        SuppressionDoublonLettre(lien_temporaire);   // Supprime les doublons

        sort(lien_temporaire.begin(), lien_temporaire.end());


        // Pour chaque lettre lue, se déroule l'état en cours
        for (int i = 0; i < lien_temporaire.size(); i++) 
        {
            // Pour chaque état compris par l'état en cours
            for (int j = 0; j < VectorEtatTemporaire[iterateur].liste_etat_actuel.size(); j++) 
            {
                // Recherche des états
                for (int k = 0; k < liste_etat.size(); k++) 
                {
                    if (liste_etat[k].getEtat() == VectorEtatTemporaire[iterateur].liste_etat_actuel[j]) 
                    {
                        for (int l = 0; l < liste_etat[k].transition_etat.size(); l++) 
                        {
                            if (liste_etat[k].transition_etat[l].lien == lien_temporaire[i]) 
                            {
                                EtatTemporaire.liste_etat_actuel.push_back(liste_etat[k].transition_etat[l].fin);
                            }
                        }
                    }
                }      
            }   // Fin de parcours des transitions d(états de l'état en cours
        
            SuppressionDoublonCible(EtatTemporaire.liste_etat_actuel);

            int etat_trouve = 0;  // Retourne l'état trouvé

            // rechercher si tmpState , n'existe pas deja
            // Si il existe :
            if (ComparerEtat(EtatTemporaire, VectorEtatTemporaire, etat_trouve)) 
            {
                // On décrémente le compteur en prévision de la fonction ReinitialiserEtat.
                EtatTemporaire.modifierEtat(EtatTemporaire.getEtat() - 1);
            } 
            else
            {  
                // S'il n'existe pas: recherche si le futur état est final
                for (int j = 0; j < EtatTemporaire.liste_etat_actuel.size(); j++) 
                {
                    for (int k = 0; k < etats_finaux.size(); k++) 
                    {
                        if (EtatTemporaire.liste_etat_actuel[j] == etats_finaux[k]) 
                        {
                            EtatTemporaire.modifierEtatFinal(true);
                        }
                    }
                }

                // On rajoute l'état au vecteur d'états
                VectorEtatTemporaire.push_back(Etat(EtatTemporaire));
                // On sauvegarde son numéro pour ajouter les transitions
                etat_trouve = EtatTemporaire.getEtat();

            } // Fin si (l'état existe)

            // On met à jour les transitons de iterateur vers le nouvel état
            // Numéro d'état contenu dans etat_trouve, soit recupérer, soit incrémenté
            VectorEtatTemporaire[iterateur].transition_etat.push_back(Transition(VectorEtatTemporaire[iterateur].getEtat(), lien_temporaire[i], etat_trouve));
            SuppressionDoublonTransition(VectorEtatTemporaire[iterateur].transition_etat);

            // On réinitialise le vecteur temporaire
            ReinitialiserEtat(EtatTemporaire);
        }   // fin de lecture alphabet de l'etat en cour
    
        lien_temporaire.clear();
        iterateur++; // Tant qu'on a pas atteint la fin de la pile d'etat
    }     // fin de traitement des états

    // reconstitution de l'automate
    etats_initiaux.clear();
    etats_initiaux.push_back(1);      // le premier etat est forcement initial

    etats_finaux.clear();
    table_transition.clear();
    liste_etat.clear();

    for (int i = 0; i < VectorEtatTemporaire.size(); i++) 
    {
        if (VectorEtatTemporaire[i].getFin()) 
        {
            etats_finaux.push_back(VectorEtatTemporaire[i].getEtat());
        }
        for (int j = 0; j < VectorEtatTemporaire[i].transition_etat.size(); j++) 
        {
            table_transition.push_back(VectorEtatTemporaire[i].transition_etat[j]);
        }
    }
    
    liste_etat = VectorEtatTemporaire;

    wcout << L">>> L'automate est désormais déterministe." << endl;
}

int Automate::getNombreEtats()
{
    return liste_etat.size();
}

int Automate::getNombreCaracteresAlphabet()
{
    return alphabet.size();
}

int Automate::getNombreTransitions()
{
    return table_transition.size();
}

void Automate::DecalageListeEtats()
{
    liste_etat.push_back(Etat(0, true, false));
    vector <Etat> tmp;
    tmp.push_back(Etat(0, true, false));

    for (int i = 1; i < liste_etat.size(); i++)
    {
        tmp.push_back(liste_etat[i]);
    }

    for (int i = 0; i < liste_etat.size(); i++)
    {
        liste_etat[i] = tmp[i];
    }
}

void Automate::DecalageListeTransitions()
{
    table_transition.push_back(Transition(0, "a", 0));
    table_transition.push_back(Transition(0, "b", 0));
    vector <Transition> tmp;
    tmp.push_back(Transition(0, "a", 0));
    tmp.push_back(Transition(0, "b", 0));

    for (int i = 2; i < table_transition.size(); i++)
    {
        tmp.push_back(table_transition[i]);
    }

    for (int i = 0; i < table_transition.size(); i++)
    {
        table_transition[i] = tmp[i];
    }
}

void Automate::LireMot(int option)
{
    string mot;
    bool vide = false;
    int choix = menu3();

    if (choix == 1) 
    {
        switch (option)
        {
            case 1:
            this->AfficherAutomate(1, "Automate initial A1"); // Rappel de la table
            wcout << endl << L"Veuillez entrer le mot à tester par l'automate: ";
            cin >> mot;
            cout << endl << ">>> Lecture du mot: " << mot << endl;
            break;

            case 2:
            this->AfficherAutomate(3, "Automate deterministe A3"); // Rappel de la table
            wcout << endl << L"Veuillez entrer le mot à tester par l'automate: ";
            cin >> mot;
            cout << endl << ">>> Lecture du mot: " << mot << endl;
            break;

            case 3:
            this->AfficherAutomate(4, "Automate deterministe complet A4"); // Rappel de la table
            wcout << endl << L"Veuillez entrer le mot à tester par l'automate: ";
            cin >> mot;
            cout << endl << ">>> Lecture du mot: " << mot << endl;
            break;

            case 4:
            this->AfficherAutomate(5, "Automate deterministe complet minimal A5"); // Rappel de la table
            wcout << endl << L"Veuillez entrer le mot à tester par l'automate: ";
            cin >> mot;
            cout << endl << ">>> Lecture du mot: " << mot << endl;
            break;
        }
    } 
    else 
    {
        vide = true;
    }

    //
    if (vide == true) 
    {   
        // Pour un mot vide, l'état initial doit être aussi final
        vide = false;

        for (int i = 0; i < etats_initiaux.size(); i++) 
        {
            for (int j = 0; j < etats_finaux.size() && !vide; j++) 
            {
                // Condition du mot vide validée 
                if (etats_initiaux[i] == etats_finaux[j]) 
                {
                    vide = true;
                }
            }
        }

        if (vide == true) 
        {
            wcout << endl << L"Cet automate reconnaît le mot vide." << endl;
        } 
        else 
        {
            wcout << endl << L"Cet automate ne reconnaît pas le mot vide." << endl;   
        }

    } 
    else 
    {
        int etat_utilise = etats_initiaux[0]; // On part de l'état initial
        bool continuer = false; // Pour vérifier si on continue de lire le mot
        string temporaire;

        for (int i = 0; i < mot.size() && !continuer; i++) 
        {
            continuer = true;

            for (int j = 0; j < table_transition.size() && continuer; j++) 
            {
                temporaire = mot[i];

                if ((table_transition[j].debut == etat_utilise) && (table_transition[j].lien == temporaire)) 
                {
                    etat_utilise = table_transition[j].fin;
                    continuer = false;
                }
            }
            
            if (continuer) 
            {
                // Dans le cas où aucune transition existe
                wcout << L"Cet automate ne reconnaît pas le mot ";
                cout << mot << endl << endl;
            }
        }

        if (!continuer) 
        { 
            // Si on n'a pas fini de lire le mot
            continuer = true;

            for (int i = 0; i < etats_finaux.size() && continuer; i++) 
            {
                if (etat_utilise == etats_finaux[i]) 
                {
                    wcout << L"Cet automate reconnaît le mot ";
                    cout << mot << endl << endl;
                    return;
                }
            }
            
            if (continuer) 
            {
                wcout << L"Cet automate ne reconnaît pas le mot ";
                cout << mot << endl << endl;
            }
        }
    }
}

void Automate::Minimisation() 
{
    cout << ">>> Minimisation de l'automate..." << endl << endl;

    // Initialisation de la prèmiere partition
    wcout << L">>> Étape 1: Initialisation de la première partition (T / NT)" << endl;
    vector <vector <int> > etat(liste_etat.size());
    vector <vector <int> > partition(2); // État des partitions

    for (unsigned int i = 0; i < liste_etat.size(); i++)
    {
        etat[i].push_back(liste_etat[i].getEtat());

        // S'il est final (T)
        if (liste_etat[i].getFin()) 
        {   
            etat[i].push_back(1);
            partition[1].push_back(liste_etat[i].getEtat());
        } 
        else // Non Terminal (NT)
        {
            etat[i].push_back(2);
            partition[0].push_back(liste_etat[i].getEtat());
        }
    }

    wcout << L">>> Étape 2: Création de la première partition" << endl << endl;
    for (unsigned int i = 0; i < liste_etat.size(); i++) 
    {
        for (unsigned int j = 0; j < liste_etat[i].transition_etat.size(); j++) 
        {
            for (unsigned int k = 0; k < etat.size(); k++) 
            {
                if (liste_etat[i].transition_etat[j].fin == etat[k][0]) 
                {
                    etat[i].push_back(etat[k][1]);
                }
            }
        }
    }
    // Fin de la création de la première partition

    AfficherAutomateMinimal(etat);  // Affichage de la première table de transitions

    bool trouve = false, partie1_trouve = false, partie2_trouve = false; // Calidité de l'état
    unsigned int taille_partition = 0, iteration = 0;
    vector <vector <int> > urgence = partition;
    wcout << L">>> Étape 3: Lancement de la boucle de minimisation de l'automate..." << endl;

    /* Boucle de minimisation: tant qu'on a de nouveaux états, ou tant qu'on a autant d'états que de partitions.
       - On sépare les partitions */
    while (partition.size() > taille_partition && partition.size() != liste_etat.size()) 
    {
        iteration++;
        Pause();

        wcout << L"* Itération " << iteration << endl << endl; 
        taille_partition = partition.size();   // Pour savoir si le nombre de partitions a changé

        // On efface les partitions pour les recréer après

        // Comparaison des partitions etat par etat: recherche des états identiques
        for (unsigned int i = 0; i < liste_etat.size(); i++) 
        {
            for (unsigned int j = 0; j < liste_etat.size(); j++) 
            {
                trouve = true;

                for (unsigned int k = 1; k < etat[i].size(); k++) 
                {
                    if (i != j && i < j && trouve) 
                    {   
                        // Si on ne regarde pas le même etat ou n états précédents et qu'on doit continuer
                        if (etat[i][k] != etat[j][k] && trouve) 
                        {
                            trouve = false;
                        } 
                        else 
                        {
                            trouve = true;
                        }
                    } 
                    else 
                    {   
                        trouve = false; // si i = j ou i > j
                    }
                }     

                // Si on a trouver tous les états de la table actuelle ou s'ils ont la même partition
                if (trouve) 
                {
                    // Redéfinition de la table des partitions.
                    partie1_trouve = partie2_trouve = false;
                    
                    unsigned int k = 0;

                    for (k = 0; k < partition.size() && !(partie1_trouve || partie2_trouve); k++) 
                    {
                        if (partition[k].size() > 0) 
                        {       
                            for (int l = 0; l < partition[k].size(); l++) 
                            {
                                if (partition[k][l] == etat[i][0]) 
                                {
                                    partie1_trouve = true;
                                }

                                if (partition[k][l] == etat[j][0]) 
                                {
                                    partie2_trouve = true;
                                }
                            }
                        }
                    }
                    
                    k--;  // Sortie de boucle: k est décrémenté ...

                    if (partie1_trouve || partie2_trouve) 
                    {
                        if (partie1_trouve && !partie2_trouve) 
                        {
                            partition[k].push_back(etat[j][0]);
                        }
                        else if (!partie1_trouve && partie2_trouve) 
                        {
                            partition[k].push_back(etat[i][0]);
                        }
                    } 
                    else 
                    {   
                        // Les états n'étaient dans aucune partition existante: nouvelle ligne dans la table
                        partition.resize(partition.size() + 1);
                        partition[partition.size() - 1].push_back(partition[i][0]);
                        partition[partition.size() - 1].push_back(partition[j][0]);
                    }
                }      
            } 
        }   
        
        // Si l'état n'a aucun équivalent, il est tout seul dans sa partition
        for (int i = 0; i < etat.size(); i++) 
        {    
            partie1_trouve = false; // Pour chaque état

            for (int j = 0; j < partition.size(); j++) 
            {   
                // On le cherche dans la table de partitions
                for (int k = 0; k < partition[j].size(); k++) 
                {
                    if (partition[j][k] == etat[i][0]) 
                    {
                        partie1_trouve = true;
                    }
                }
            }

            if (!partie1_trouve) 
            {   
                // Si on ne l'a pas trouvé: on le rajoute dans la table de partitions
                partition.resize(partition.size() + 1);
                partition[partition.size() - 1].push_back(partition[i][0]);
            }
        }

        wcout << L"État des partitions après traitement:" << endl;
        
        for (int i = 0; i < partition.size(); i++) 
        {
            cout << " " << intToGroupe(i + 1) << " : ";

            for (int j = 0; j < partition[i].size(); j++) 
            {
                cout << partition[i][j] << " ";
            } 
            cout << endl;
        }
        cout << endl;
        // La nouvelle table de partition a été crée


        // Mise à jour du statut de "etat" par rapport à la nouvelle table de partitions.
        for (int i = 0; i < partition.size(); i++) 
        {
            for (int j = 0; j < partition[i].size(); j++) 
            {
                for (int k = 0; k < etat.size(); k++) 
                {
                    if (partition[i][j] == etat[k][0]) 
                    {
                        etat[k][1] = i + 1;
                    }
                }
            }
        }

        // Mise à jour des partitions
        for (int i = 0; i < liste_etat.size(); i++) 
        {
            int compteur_lien = 2;

            for (int j = 0; j < liste_etat[i].transition_etat.size(); j++) 
            {
                for (int k = 0; k < etat.size(); k++) 
                {
                    if (liste_etat[i].transition_etat[j].fin == etat[k][0] && compteur_lien <= alphabet.size() + 2) 
                    {
                        etat[i][compteur_lien] = etat[k][1];
                        compteur_lien++;
                    }
                }
            }
        }

        AfficherAutomateMinimal(etat);
        partition.clear();
    }  // Fin boucle while (minimisation)

    /*
        # Reconsituer l'etat minimal en mémoire
        # effacer l'etat
        # creer les etats correspondant aux partitions
        # mettre a jour les etats correspondant et les transition
        # mettre a jour la table de transition de l'automate
    */

    if (partition.size() == liste_etat.size()) 
    {
        wcout << endl << L"Cet automate est déjà minimal" << endl;
        wcout << L">>> Étape 4: Sauvegarde de l'état minimal de l'automate en mémoire..." << endl;
    } 
    else 
    {
        wcout << endl << L">>> Minimisation terminée: cet automate est désormais minimal" << endl;
        wcout << L">>> Étape 4: Sauvegarde de l'état minimal de l'automate en mémoire..." << endl;
    }
    
    cout << endl;


    // Mise à jour de l'état
    Etat EtatTemporaire;
    int numero_etat = 0;

    liste_etat.clear();
    table_transition.clear();
    
    for (int i = 0; i < partition.size(); i++) 
    {
        // Recherche du numéro de la partition associée
        for (int j = 0; j < etat.size(); j++) 
        {
            for (int k = 0; k < partition[i].size(); k++) 
            {
                if (partition[i][k] == etat[j][0]) 
                {
                    numero_etat = etat[j][1];
                }
            }
        }

        EtatTemporaire.modifierEtat(numero_etat);

        // Recherche des liste des états de l'état ciblé
        for (int j = 0; j < partition[i].size(); j++) 
        {
            EtatTemporaire.liste_etat_actuel.push_back(partition[i][j]);

            for (int k = 0; k < etats_initiaux.size(); k++) 
            {
                if (etats_initiaux[k] == partition[i][j]) 
                {
                    EtatTemporaire.modifierEtatInitial(true);
                }
                
                for (int k = 0; k < etats_finaux.size(); k++) 
                {
                    if (etats_finaux[k] == partition[i][j]) 
                    {
                        EtatTemporaire.modifierEtatFinal(true);
                    }
                }
            }
            
            // Remplissage de la table de transitions
            for (int j = 0; j < etat.size(); j++) 
            {
                trouve = false;

                // Si on est à l'état correspondant
                if (etat[j][1] == numero_etat && !trouve) 
                {   
                    trouve = true;

                    for (int k = 0; k < alphabet.size(); k++) 
                    {
                        EtatTemporaire.transition_etat.push_back(Transition(numero_etat, alphabet[k], etat[j][k + 2])); 
                        table_transition.push_back(Transition(numero_etat, alphabet[k], etat[j][k + 2]));
                    }
                }
            }

            liste_etat.push_back(EtatTemporaire);
            ReinitialiserEtat(EtatTemporaire);
    }

        // On met à jour les états: Terminal / Initial
        etats_initiaux.clear();
        etats_finaux.clear();

        for (int i = 0; i < liste_etat.size(); i++) 
        {
            if (liste_etat[i].getDebut()) 
            {
                etats_initiaux.push_back(liste_etat[i].getEtat());
            }
            
            if (liste_etat[i].getFin()) 
            {
                etats_finaux.push_back(liste_etat[i].getEtat());
            }
        }
    }
}

// On va se servir d'un tableau dynamique (vector) à 2 dimensions
void Automate::AfficherAutomateMinimal(vector <vector <int> > etat) 
{
    // Affichage de l'automate. 
    cout << "  E/S   | Etat || Part ||";

    for (int i = 0; i < alphabet.size(); i++) 
    {
        cout << "  " << alphabet[i] << "  |";
    }

    cout << endl << "-------------------------";

    for (int j = 0; j < alphabet.size(); j++) 
    {
        cout << "------";
    }
    
    string temporaire;

    bool trouveDebut, trouveFin;

    cout << endl;
    
    for (int i = 0; i < liste_etat.size(); i++) 
    {
        for (int j = 0; j < etat[i].size(); j++) 
        {
            if (j == 0) 
            {
                trouveDebut = trouveFin = false;

                for (int k = 0; k < etats_initiaux.size(); k++) 
                {
                    if (etats_initiaux[k] == liste_etat[i].getEtat()) 
                    {
                        trouveDebut = true;
                    }
                }       

                for (int k = 0; k < etats_finaux.size(); k++) 
                {
                    if (etats_finaux[k] == liste_etat[i].getEtat()) 
                    {
                        trouveFin = true;
                    }
                }

                if (trouveDebut) 
                {
                    // Initial + final
                    if (trouveDebut) 
                    { 
                        cout << "  <-->";
                    } 
                    else 
                    {      
                        // Seulement initial
                        cout << "  --> ";
                    }
                }  
                else 
                {
                    if (trouveFin) 
                    { 
                        // Juste final
                        cout << "  <-- ";
                    }
                    else 
                    {      
                        // Rien du tout
                        cout << "      ";
                    }
                }
                
                cout << "  | ";
                cout << "  " << etat[i][j] << "  ||";
            }
            
            // Affichage des partitions
            if (j == 1) 
            {
                temporaire = intToGroupe(etat[i][j]);

                if (temporaire.size() == 1) 
                {
                    cout << "   " << temporaire << "  ||";
                }

                if (temporaire.size() == 2) 
                {
                    cout << "  " << temporaire << "  ||";
                }

                if (temporaire.size() == 3) 
                {
                    cout << "  " << temporaire << " ||";
                }
                if (temporaire.size() == 4) 
                {
                    cout << " " << temporaire << " ||";
                }
            }

            if (j > 1) 
            {
                temporaire = intToGroupe(etat[i][j]);

                if (temporaire.size() == 1) 
                {
                    cout << "  " << temporaire << "  |";
                }

                if (temporaire.size() == 2) 
                {
                    cout << "  " << temporaire << " |";
                }

                if (temporaire.size() == 3) 
                {
                    cout << " " << temporaire << " |";
                }

                if (temporaire.size() == 4) 
                {
                    cout << " " << temporaire << "|";
                }
            }
        }

        cout << endl << "-------------------------";

        for (int j = 0; j < alphabet.size(); j++) 
        {
            cout << "------";
        }

        cout << endl;
    }
}

void Pause()
{
	wcout << L"Appuyer sur entrée pour continuer ";
	cin.ignore().get(); // Cette commande de saisie sécurisée ordonne a l'utilisateur d'appuyer sur entrée (et seul entrée marche)

	return;
}