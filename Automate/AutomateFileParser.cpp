#include "AutomateFileParser.h"

AutomateFileParser::AutomateFileParser()
{
	// Des choses � init ?
}

//Charge en m�moire le fichier contenant les donn�es de l'automate
void AutomateFileParser::loadFile(string path)
{
	// Charge le fichier representant l'automate en memoire
}

//G�n�re l'automate � partir du fichier
Automate& AutomateFileParser::generate()
{
	Automate a(this->getAlphabet());

	// ...

	return a;
}

//Extrait l'alphabet du fichier
string AutomateFileParser::getAlphabet()
{
	return ""; //TODO
}

//Passe ou non le parser en mode debug
void AutomateFileParser::setDebugged(bool b)
{
	this->isDebugged = b;
}
