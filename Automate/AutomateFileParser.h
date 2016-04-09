#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Automate.h"

#define private public

class AutomateFileParser
{

private:
	string path;
	bool fileLoaded = false;
	ifstream file;

	bool isDebugged = false;

public:
	AutomateFileParser();
	~AutomateFileParser();
	void loadFile(string path);
	Automate* generate();

	string getAlphabet();
	// ...

	void setDebugged(bool b);

private:
	void convertStringToArray(string s, int** tab, int* size);
	void convertStringToTransitionData(string s, int * from, char * label, int * to);
	string generateAlphabet(int n);
};