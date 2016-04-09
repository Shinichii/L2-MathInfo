#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //Pour std::find

#define private public

using namespace std;

//Classe contenant un automate et sa logique simple
class Automate
{
	//Classe representant une transition etat -> label -> etat
	class Transition
	{
		public:
		int from;
		int to;
		char label;

		Transition(int f, char l, int t) : from(f), to(t), label(l){}

		friend bool operator==(const Transition& a, const Transition& b)
		{
			return a.from == b.from && a.label == b.label && a.to == b.to;
		}

		friend ostream& operator<<(ostream& stream, const Transition& t)
		{
			stream << "[" << t.from << " -> " << t.label << " -> " << t.to << "]";
			return stream;
		}
	};

private:
	vector<Transition> transitions;
	vector<int> etats;
	vector<int> entrees;
	vector<int> sorties;
	string alphabet;

	bool debugged = false;

public:
	Automate(string alphabet);
	void ajouterEntree(int etat);
	void ajouterSortie(int etat);
	bool etatEstEntree(int etat);
	bool etatEstSortie(int etat);
	bool etatExiste(int etat);
	void ajouterEtat(int etat);
	void ajouterTransition(int from, char label, int to);
	void ajouterTransition(Transition t);
	
	bool reconnaitMot(string s);
	bool estSynchrone();
	bool estDeterministe();
	bool estComplet();

	void setDebugged(bool b);

	friend ostream& operator<<(ostream& stream, const Automate& a);

private:
	Transition * trouverTransition(int etat, char label);

};