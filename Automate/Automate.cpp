#include "Automate.h"


//Cree l'automate vide à partir de son alphabet
Automate::Automate(string alphabet)
{
	this->alphabet = alphabet;
}

//Ajoute une entree a l'automate
void Automate::ajouterEntree(int etat)
{
	bool entreeExiste = find(entrees.begin(), entrees.end(), etat) != entrees.end();

	if(!entreeExiste)
	{
		entrees.push_back(etat);
		makeDirty();
	}
	else if(debugged)
		cout << "[INFO] On ne peut ajouter l'entree " << etat << ", elle existe deja." << endl;
}

//Ajoute une sortie à l'automate
void Automate::ajouterSortie(int etat)
{
	bool sortieExiste = find(sorties.begin(), sorties.end(), etat) != sorties.end();

	if(!sortieExiste)
	{
		sorties.push_back(etat);
		makeDirty();
	}
	else if(debugged)
		cout << "[INFO] On ne peut ajouter la sortie " << etat << ", elle existe deja." << endl;
}

//Indique si l'etat existe
bool Automate::etatExiste(int etat)
{
	return find(etats.begin(), etats.end(), etat) != etats.end();
}

//Ajoute un etat à la liste d'états
void Automate::ajouterEtat(int etat)
{
	if(!etatExiste(etat))
	{
		etats.push_back(etat);
		makeDirty();
	}
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

//Ajoute une transition à l'automate à partir de ses composantes
void Automate::ajouterTransition(int from, char label, int to)
{
	Transition t(from, label, to);
	this->ajouterTransition(t);
}

//Ajoute une transition à l'automate
void Automate::ajouterTransition(Transition t)
{
	if(debugged) cout << "# Ajout de la transition: " << t << endl;

	bool transitionExiste = find(transitions.begin(), transitions.end(), t) != transitions.end();

	if(!transitionExiste)
	{
		transitions.push_back(t);

		if(!etatExiste(t.from))
			ajouterEtat(t.from);
		if(!etatExiste(t.to))
			ajouterEtat(t.to);

		makeDirty();
	}
	else if(debugged)
		cout << "\t[ERREUR] La transition existe déjà!" << endl;
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
			//On regarde si l'état est sortie et on retourne en fonction
			return etatEstSortie(etatCourant);
		}
		else
		{
			//On cherche une transition partant de etatCourant et labelée caractereCourant
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

//Teste le synchronisme d'un automate
bool Automate::estSynchrone()
{
	//Cache
	if(!dirtySynchrone && cacheEnabled) return etaitSynchrone;

	for (int i = 0; i < etats.size(); i++)
	{
		if (trouverTransition(i, '%') != nullptr)
		{
			//On stocke le resultat dans le cache
			cacheTest(&dirtySynchrone, &etaitSynchrone, false);

			//Si on trouve une transition mot vide
			return false;
		}
	}

	//On stocke le resultat dans le cache
	cacheTest(&dirtySynchrone, &etaitSynchrone, true);

	return true;
}

//Teste le determinisme de l'automate
bool Automate::estDeterministe()
{
	//Cache
	if(!dirtyDeterministe && cacheEnabled) return etaitDeterministe;

	//On verifie le nombre d'états d'entree, s'il en a plus d'un, l'automate n'est pas déterministe
	if (entrees.size() != 1)
	{
		//On stocke le resultat dans le cache
		cacheTest(&dirtyDeterministe, &etaitDeterministe, false);

		return false;
	}
	//Dans le cas où il n'y a qu'une seule entrée il faut vérifier CHAQUE état qu'il n'y ait bien qu'une seule transition libelle 
	for (int i = 0; i < etats.size(); i++)
	{
		for (int j = 0; j < transitions.size(); j++)
		{
			for (int k = 0; k < transitions.size(); k++)
			{
				if (k != j && transitions.at(k).from == transitions.at(j).from && transitions.at(k).label == transitions.at(j).from)
				{
					//On stocke le resultat dans le cache
					cacheTest(&dirtyDeterministe, &etaitDeterministe, false);

					return false;
				}
			}
		}
	}

	//On stocke le resultat dans le cache
	cacheTest(&dirtyDeterministe, &etaitDeterministe, true);

	return true;
}

//Teste la completion d'un automate
bool Automate::estComplet()
{
	//Cache
	if(!dirtyComplet && cacheEnabled) return etaitComplet;

	//On parcours tous les états
	for(int i = 0; i < etats.size(); i++)
	{
		//On parcours tous les caracteres de l'alphabet
		for(int j = 0; j < alphabet.length(); j++)
		{
			char c = alphabet.at(j);

			//Une transition existe-t-elle pour cette lettre et cet état ?
			if(trouverTransition(i, c) == nullptr)
			{
				//On stocke le resultat dans le cache
				cacheTest(&dirtyComplet, &etaitComplet, false);

				//Si il en manque une, il n'est pas complet0
				return false;
			}
		}
	}

	//On stocke le resultat dans le cache
	cacheTest(&dirtyComplet, &etaitComplet, true);

	return true;
}

//Invalide le cache de tests
void Automate::makeDirty()
{
	dirtyComplet = true;
	dirtySynchrone = true;
	dirtyDeterministe = true;
}

//Passe le flag dirty à false, et cache la valeur val dans state
void Automate::cacheTest(bool * dirtyFlag, bool * state, bool val)
{
	if(cacheEnabled)
	{
		*dirtyFlag = false;
		*state = val;
	}
}

void Automate::setCached(bool b)
{
	this->cacheEnabled = b;
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
