#include <iostream>
#include <string>
#include "Automate.h"

//Fonction principale pour l'instant peuplée de tests ridicules
int main(int argc, char * argv[])
{
	Automate a("ab");

	a.setDebugged(true);

	a.ajouterTransition(0, 'a', 0);
	a.ajouterTransition(0, 'b', 1);

	a.ajouterEntree(0);
	a.ajouterSortie(1);

	cout << "Reconnait mot 'aaaba' ? " << a.reconnaitMot("aaaba") << endl;

	system("pause");
}