#include <iostream>
#include <string>
#include "Automate.h"
#include "AutomateFileParser.h"
#include "AutomateTests.h"

int main(int argc, char * argv[])
{
	AutomateFileParser afp;
	afp.setDebugged(true);
	afp.loadFile("automate_presque_complet1.txt");

	try
	{
		Automate a = *afp.generate();
		a.setDebugged(true);
		a.ajouterTransition(0, 'a', 0);
		a.ajouterTransition(0, 'b', 1);
		a.ajouterEntree(0);
		a.ajouterSortie(1);
		
		cout << endl << a << endl << endl;

		cout << "Reconnait mot 'aaaba' ? " << a.reconnaitMot("aaaba") << endl << endl;

		suite_Tests(a);
	}
	catch(exception& e)
	{
		cout << "[EXCEPTION] " << e.what() << endl;
	}

	system("pause");
}