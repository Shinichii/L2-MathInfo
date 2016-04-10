#include "AutomateTests.h"

void suite_Tests(Automate a)
{
	if (!a.estSynchrone())
	{
		cout << "L'automate est asynchrone" << endl;
		//Appeler l'algo de déterminisation synchrone
		return;
	}
	cout << "L'automate est synchrone" << endl;
	if (!a.estDeterministe())
	{
		cout << "L'automate n'est PAS deterministe" << endl;
		return;
		//Appeler l'algo de determinisation synchrone
	}
	cout << "L'automate est deterministe" << endl;
	if (!a.estComplet())
	{
		cout << "L'automate n'est pas complet" << endl;
		return;
		//Appeler l'algo de completion
	}
	cout << "L'automate est complet" << endl;
	return;
}