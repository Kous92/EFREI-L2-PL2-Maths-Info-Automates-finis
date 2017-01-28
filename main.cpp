#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-etat.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-automate.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-menu.h"

using namespace std;

int main(void)
{
	int fini = 1;
	do
	{
		int choix = menu();
		int nb_options = 0;


		switch (choix)
		{
			case 1:
			choix = 1;
			break;

			case 2:
			choix = 2;
			break;

			case 3:
			choix = 3;
			break;

			case 4:
			choix = 4;
			break;

			case 5:
			choix = 5;
			break;

			case 6:
			choix = 6;
			break;

			case 7:
			choix = 8;
			break;

			case 8:
			choix = 9;
			break;

			case 9:
			choix = 12;
			break;

			case 10:
			choix = 13;
			break;

			case 11:
			choix = 15;
			break;

			case 12:
			choix = 19;
			break;

			case 13:
			choix = 72;
			break;

			case 14:
			choix = 73;
			break;

			case 15:
			choix = 79;
			break;

			case 16:
			choix = 80;
			break;

			case 17:
			choix = 85;
			break;

			case 18:
			choix = 92;
			break;

			case 19:
			choix = 96;
			break;

			case 20:
			choix = 99;
			break;

			case 21:
			choix = 101;
			break;
			
			case 22:
			choix = 102;
			break;

			case 23:
			choix = 103;
			break;

			case 24:
			choix = 104;
			break;

			case 25:
			choix = 106;
			break;

			case 26:
			choix = 107;
			break;

			case 27:
			choix = 108;
			break;

			case 28:
			choix = 109;
			break;

			case 29:
			choix = 110;
			break;

			case 30:
			choix = 111;
			break;

			case 31:
			choix = 113;
			break;

			case 32:
			choix = 114;
			break;

			case 33:
			choix = 115;
			break;

			case 34:
			choix = 116;
			break;

			case 35:
			choix = 117;
			break;

			case 36:
			choix = 118;
			break;

			default:
			cerr << ">>> Erreur inconnue !" << endl;
			return EXIT_FAILURE;
			break;
		}

		stringstream ss;
		ss << choix;
		string nom_fichier = "test/test" + ss.str() + ".txt";

		Automate A1;

		if (A1.LireFichier(nom_fichier) == false)
		{
			cerr << "Erreur: nom du fichier invalide !" << endl;

			return EXIT_FAILURE;
		}
		else
		{
			wcout << L"Fichier chargé avec succès" << endl << endl;
		}

		Pause();
		system("clear");
		
		A1.AfficherAutomate(1, nom_fichier);

		if (A1.EstAsynchrone() == true)
		{
			wcout << L">>> Cet automate est asynchrone." << endl;
		}
		else
		{
			wcout << L">>> Cet automate est synchrone." << endl;
		}

		nb_options++;

		Automate A2 = A1;

		if (A2.EstStandard() == true)
		{
			wcout << L">>> Cet automate est standard." << endl;
		}
		else
		{
			wcout << L">>> Cet automate est non-standard." << endl;
			A2.Standardisation();
			Pause();
			A2.AfficherAutomate(2, nom_fichier);
			Pause();
		}

		
		Automate A3 = A1;

		system("clear");

		if (A3.EstDeterministe() == true)
		{
			wcout << L">>> Cet automate est déterministe." << endl;
			A3.AfficherAutomate(3, nom_fichier);
			Pause();
			nb_options++;
		}
		else
		{
			wcout << L">>> Cet automate est non-déterministe." << endl;
			A3.Determinisation();
			A3.AfficherAutomate(3, nom_fichier);
			nb_options++;
			Pause();
		}

		system("clear");
		Automate A4 = A3;

		if (A4.EstComplet() == true)
		{
			wcout << L">>> Cet automate est complet." << endl;

			// Vérification de l'état poubelle
			if (A4.Completion(true))
			{
				wcout << L">>> Un état poubelle implicite est présent dans cet automate." << endl;
				A4.AfficherAutomate(4, nom_fichier);
				nb_options++;
				Pause();
			}
			else
			{
				A4.AfficherAutomate(3, nom_fichier);
				nb_options++;
				Pause();
			}
		}
		else
		{
			wcout << L">>> Cet automate n'est pas complet." << endl;
			A4.Completion(false);
			A4.AfficherAutomate(4, nom_fichier);
			nb_options++;
			Pause();
		}

		// Minimisation: L'automate est déterministe et complet
		Automate A5 = A4;
		A5.Minimisation();
		nb_options = 4;
		Pause();

		switch (nb_options)
		{
			case 1:
			choix = menu4(nb_options, A1);
			break;

			case 2:
			choix = menu4(nb_options, A3);
			break;

			case 3:
			choix = menu4(nb_options, A4);
			break;

			case 4:
			choix = menu4(nb_options, A5);
			break;

			default:
			cerr << ">>> Erreur inconnue !" << endl;
			return EXIT_FAILURE;
			break;
		}

		switch (choix)
		{
			case 1:
			A1.LireMot(1);
			break;

			case 2:
			A3.LireMot(2);
			break;

			case 3:
			A4.LireMot(3);
			break;

			case 4:
			A5.LireMot(4);
			break;

			default:
			cerr << ">>> Erreur inconnue !" << endl;
			return EXIT_FAILURE;
			break;
		}

		Pause();
		fini = menu2();

	} while (fini == 1); 

	return 0;
}