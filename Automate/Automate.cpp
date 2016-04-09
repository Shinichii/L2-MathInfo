#include "Automate.h"

//Cree l'automate vide � partir de son alphabet
Automate::Automate(string alphabet)
{
	this->alphabet = alphabet;
}

//Ajoute une entree a l'automate
void Automate::ajouterEntree(int etat)
{
	bool etatExiste = find(etats.begin(), etats.end(), etat) != etats.end();

	if(!etatExiste)
		entrees.push_back(etat);
	else if(debugged)
		cout << "[INFO] On ne peut ajouter l'entree " << etat << ", elle existe deja." << endl;
}

//Ajoute une sortie � l'automate
void Automate::ajouterSortie(int etat)
{
	bool etatExiste = find(sorties.begin(), sorties.end(), etat) != sorties.end();

	if(!etatExiste)
		sorties.push_back(etat);
	else if(debugged)
		cout << "[INFO] On ne peut ajouter la sortie " << etat << ", elle existe deja." << endl;
}

//Indique si un etat est une entree
bool Automate::etatEstEntree(int etat)
{
	return find(entrees.begin(), entrees.end(), etat) != entrees.end();
}

//Indique si un etat est une sortie
bool Automate::etatEstSortie(int etat)
{
	return find(sorties.begin(), sorties.end(), etat) != sorties.end();
}

//Ajoute une transition � l'automate � partir de ses composantes
void Automate::ajouterTransition(int from, char label, int to)
{
	Transition t(from, label, to);
	this->ajouterTransition(t);
}

//Ajoute une transition � l'automate
void Automate::ajouterTransition(Transition t)
{
	if(debugged) cout << "# Ajout de la transition: " << t << endl;

	bool transitionExiste = find(transitions.begin(), transitions.end(), t) != transitions.end();

	if(!transitionExiste)
	{
		transitions.push_back(t);
	}
	else if(debugged)
		cout << "\t[ERREUR] La transition existe d�j�!" << endl;
}

//Fonction sur les automates deterministes
bool Automate::reconnaitMot(string s)
{
	if(debugged) cout << "# L'automate reconnait-il '" << s << "' ?" << endl;

	if(entrees.size() == 0) 
	{
		if(debugged) cout << "\t[ERREUR] L'automate n'a pas d'entrees!" << endl;
		return false;
	}

	int etatCourant = entrees.at(0);
	
	//On parcours toute la chaine de caractere
	for(int i = 0; i < s.length(); i++)
	{
		char caractereCourant = s.at(i);

		//Si on a atteint la fin du mot
		if(caractereCourant == 0)
		{
			//On regarde si l'�tat est sortie et on retourne en fonction
			return etatEstSortie(etatCourant);
		}
		else
		{
			//On cherche une transition partant de etatCourant et label�e caractereCourant
			Transition * t = trouverTransition(etatCourant, caractereCourant);

			//Si elle existe, on avance vers la suite, sinon on indique que le mot n'est pas reconnu
			if(t != nullptr)
				etatCourant = t->to;
			else
			{
				if(debugged) cout << "\t[ERREUR] Aucune transition n'existe pour [" << etatCourant << " -> " << caractereCourant << " -> ... ]" << endl;
				return false;
			}
		}
	}

	return true;
}

//Passe ou non l'automate en mode de debug (messages d'erreurs/infos)
void Automate::setDebugged(bool b)
{
	this->debugged = b;
}

//Cherche une transition originant de 'etat' et de label 'label'
Automate::Transition * Automate::trouverTransition(int etat, char label)
{
	for(vector<Transition>::iterator it = transitions.begin(); it != transitions.end(); it++)
	{
		if(it->from == etat && it->label == label)
			return &(*it);
	}

	return nullptr;
}

ostream & operator<<(ostream & stream, const Automate & a)
{
	int nbSymboles = a.alphabet.length();
	int nbEtats = a.etats.size();
	int nbEntrees = a.entrees.size();
	int nbSorties = a.sorties.size();
	int nbTransitions = a.transitions.size();

	stream << "Nb symboles alphabet: " << nbSymboles << endl;
	stream << "Nb etats: " << nbEtats << endl;
	stream << "Etats initiaux: " << nbEntrees << endl << "\t";
	for(vector<int>::const_iterator it = a.entrees.begin(); it != a.entrees.end(); it++)
		stream << *it << " ";

	stream << endl << "Etats terminaux: " << nbSorties << endl << "\t";
	for(vector<int>::const_iterator it = a.sorties.begin(); it != a.sorties.end(); it++)
		stream << *it << " ";
	stream << endl;

	stream << endl << "Transitions: " << nbTransitions << endl;
	for(vector<Automate::Transition>::const_iterator it = a.transitions.begin(); it != a.transitions.end(); it++)
		stream << "\t" << *it << endl;
	stream << endl;

	return stream;
}
