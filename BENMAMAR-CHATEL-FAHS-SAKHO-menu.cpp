#include <iostream>
#include <limits>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-automate.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-etat.h"
#include "BENMAMAR-CHATEL-FAHS-SAKHO-menu.h"

using namespace std;

int menu()
{
	system("clear");

	cout << "***********************************************" << endl;
	wcout << L"***  TAI Mathématiques pour l'informatique  ***" << endl;
	wcout << L"***    Koussaïla BEN MAMAR - Loïc CHATEL    ***" << endl;
	wcout << L"***        Dylan FAHS - Manthita SAKHO      ***" << endl;
	cout << "***********************************************" << endl << endl;

	int choix = 0;
	bool check = false;

	wcout << L">>> Choisir l'automate selon les numéros indiqués " << endl;
	cout << "1: test1.txt, 2: test2.txt, 3: test3.txt" << endl;
	cout << "4: test4.txt, 5: test5.txt, 6: test6.txt" << endl;
	cout << "7: test8.txt, 8: test9.txt, 9: test12.txt" << endl;
	cout << "10: test13.txt, 11: test15.txt, 12: test19.txt" << endl;
	cout << "13: test72.txt, 14: test73.txt, 15: test79.txt" << endl;
	cout << "16: test80.txt, 17: test85.txt, 18: test92.txt" << endl;
	cout << "19: test96.txt, 20: test99.txt, 21: test101.txt" << endl;
	cout << "22: test102.txt, 23: test103.txt, 24: test104.txt" << endl;
	cout << "25: test106.txt, 26: test107.txt, 27: test108.txt" << endl;
	cout << "28: test109.txt, 29: test110.txt, 30: test111.txt" << endl;
	cout << "31: test113.txt, 32: test114.txt, 33: test115.txt" << endl;
	cout << "34: test116.txt, 35: test117.txt, 36: test118.txt" << endl << endl;

	do
	{
		cout << "Votre choix: ";
		check = cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer
		}
		else 
		{
			if ((choix < 1) || (choix > 36))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}
		}

	} while (((choix < 1) || (choix > 36)) || (check == false));

	return choix;
}

int menu2()
{
	system("clear");

	int choix = 0;
	bool check = false;

	cout << "Voulez-vous charger un autre automate ?" << endl;
	cout << "1: Oui" << endl;
	cout << "2: Non, quitter le programme." << endl << endl;

	do
	{
		cout << "Votre choix: ";
		check = cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer
		}

		else 
		{
			if ((choix < 1) || (choix > 2))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}
		}

	} while (((choix < 1) || (choix > 2)) || (check == false));

	return choix;
}

int menu3()
{
	system("clear");

	int choix = 0;
	bool check = false;

	cout << ">>> Pour la lecture du mot: que doit faire l'automate ?" << endl;
	cout << "1: Lire un mot" << endl;
	cout << "2: Lire le mot vide" << endl << endl;

	do
	{
		cout << "Votre choix: ";
		check = cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer
		}

		else 
		{
			if ((choix < 1) || (choix > 2))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}
		}

	} while (((choix < 1) || (choix > 2)) || (check == false));

	return choix;
}

int menu4(int nb_options, Automate A)
{
	system("clear");

	int choix = 0;
	bool check = false;

	cout << ">>> Quel automate choisir pour la lecture du mot ?" << endl;

	// Automate initial (déjà déterministe ou complet)
	cout << "1: Automate initial" << endl;

	// Automate déterministe par déterminisation: option débloquée
	if ((nb_options >= 2) && (A.EstDeterministe()))
	{
		wcout << L"2: Automate déterministe" << endl;
	}
	else if ((A.EstComplet()) && (!A.EstDeterministe()))
	{
		wcout << L"2: Automate complet" << endl;
	}

	// Automate déterministe complet par complétion: option débloquée
	if (nb_options >= 3)
	{
		wcout << L"3: Automate déterministe complet" << endl;
	}

	// Automate déterministe complet minimal: option débloquée
	if (nb_options == 4)
	{
		wcout << L"4: Automate déterministe complet minimal" << endl;
	}

	do
	{
		cout << "Votre choix: ";
		check = cin >> choix;

		if (cin.fail())
		{
			cerr << "Erreur: SAISIE INVALIDE !" << endl;
			// Les 2 lignes suivantes permettent de vider le buffer: cela assure une nouvelle saisie sans avoir de boucle infinie !!!
 			cin.clear(); // Effacer les bits d'erreurs
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Supprimer la ligne erronée dans le buffer
		}

		else 
		{
			if ((choix < 1) || (choix > nb_options))
			{
				cerr << "Erreur: CHOIX INVALIDE !" << endl;
			}
		}

	} while (((choix < 1) || (choix > nb_options)) || (check == false));

	return choix;
}