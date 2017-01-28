#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

using namespace std;

class Transition
{	
	public:
	int debut;
	int fin;
	string lien;

	Transition(int Debut, string Lien, int Fin);
};

#endif