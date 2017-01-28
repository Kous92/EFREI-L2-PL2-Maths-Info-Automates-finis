#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include "BENMAMAR-CHATEL-FAHS-SAKHO-transition.h"

using namespace std;

Transition::Transition(int Debut, string Lien, int Fin)
{
	debut = Debut;
	fin = Fin;
	lien = Lien;
}