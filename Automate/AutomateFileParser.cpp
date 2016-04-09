#include "AutomateFileParser.h"

AutomateFileParser::AutomateFileParser()
{
}

AutomateFileParser::~AutomateFileParser()
{
	if(file.is_open())
		file.close();
}

//Charge en mémoire le fichier contenant les données de l'automate
void AutomateFileParser::loadFile(string path)
{
	this->path = path;

	file.open(path, ifstream::in);
	if(file.good())
	{
		fileLoaded = true;
	}
	else
	{
		if(isDebugged) cout << "[ERREUR] Impossible d'ouvrir le fichier spécifié!" << endl;
		file.close();
	}
}

//Génére l'automate à partir du fichier
Automate* AutomateFileParser::generate()
{
	if(!fileLoaded) 
	{
		if(isDebugged) cout << "[ERREUR] Impossible de generer l'automate" << endl;
		return nullptr;
	}

	int nbSymboles, nbEtats, nbTransitions, nbEtatsInitiaux, nbEtatsFinaux;
	int *etatsInitiaux, *etatsFinaux;
	Automate *automate = nullptr;

	int i = 0;
	for(string line; getline(file, line); )
	{
		if(i == 0)
		{	
			nbSymboles = std::atoi(line.c_str());
			automate = new Automate(generateAlphabet(nbSymboles));
			automate->setDebugged(isDebugged);
		}
		else if(i == 1)
		{
			nbEtats = std::atoi(line.c_str());
		}
		else if(i == 2)
		{
			convertStringToArray(line, &etatsInitiaux, &nbEtatsInitiaux);
			for(int i = 0; i < nbEtatsInitiaux; i++)
				automate->ajouterEntree(etatsInitiaux[i]);
		}
		else if(i == 3)
		{
			convertStringToArray(line, &etatsFinaux, &nbEtatsFinaux);
			for(int i = 0; i < nbEtatsFinaux; i++)
				automate->ajouterSortie(etatsFinaux[i]);
		}
		else if(i == 4)
		{
			nbTransitions = atoi(line.c_str());
		}
		else
		{
			int from, to;
			char label;
			
			convertStringToTransitionData(line, &from, &label, &to);
			automate->ajouterTransition(from, label, to);
		}

		i++;
	}

	return automate;
}

//Convertit une chaine [N x1 x2 x3] en un tableau {x1, x2, x3}
void AutomateFileParser::convertStringToArray(string s, int** tab, int* size)
{
	*tab = nullptr;
	int j = 0;

	int startChar = 0;
	int i = 0;

	while(s[i] != 0)
	{
		if(s[i] == ' ' || s[i+1] == 0)
		{
			string sub;
			if(s[i+1] == 0)
				sub = s.substr(startChar, i - startChar + 1);
			else
				sub = s.substr(startChar, i - startChar);
			startChar = i + 1;

			if(*tab == nullptr)
			{
				*size = atoi(sub.c_str());
				*tab = (int *) malloc(sizeof(int) * (*size));
			}
			else
				(*tab)[j++] = atoi(sub.c_str());	
		}

		i++;
	}
}

//Convertit une chaine [F L T] en tableau {F, L, T}
void AutomateFileParser::convertStringToTransitionData(string s, int * from, char * label, int * to)
{
	int j = 0;

	int startChar = 0;
	int i = 0;

	while(s[i] != 0)
	{
		if(s[i] >= 'a' && s[i] <= 'z')
		{
			*from = atoi(s.substr(0, i).c_str());
			*label = s.at(i);
			*to = atoi(s.substr(i+1, s.length() - i - 1).c_str());
			break;
		}

		i++;
	}
}

string AutomateFileParser::generateAlphabet(int n)
{
	if(n < 0 || n > 26)
	{
		if(isDebugged) cout << "[ERREUR] La longueur de l'alphabet spécifiée est incorrecte!" << endl;
		return "";
	}

	stringstream ss;
	for(char i = 'a'; i < 'a' + n; i++)
	{
		ss << i;
	}

	return ss.str();
}

//Passe ou non le parser en mode debug
void AutomateFileParser::setDebugged(bool b)
{
	this->isDebugged = b;
}
