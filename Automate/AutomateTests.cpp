#include "AutomateTests.h"

void suite_Tests(Automate a)
{
	cout << "Est synchrone ?" << (a.estSynchrone() ? "Oui" : "Non") << endl;
	cout << "Est deterministe ?" << (a.estDeterministe() ? "Oui" : "Non") << endl;
	cout << "Est complet? " << (a.estComplet() ? "Oui" : "Non") << endl;
}