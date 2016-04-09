#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Automate.h"

#define WINDOWS

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#define private public

class AutomateFileParser
{

private:
	string path;
	bool fileLoaded = false;
	ifstream file;
	bool isDebugged = false;

	class GenerationAutomateException : public exception
	{
		virtual const char* what() const throw()
		{
			return "Impossible de construire l'automate a partir du fichier!";
		}
	} GenerationAutomateException;

public:
	AutomateFileParser();
	~AutomateFileParser();
	void loadFile(string path);
	Automate* generate();
	void setDebugged(bool b);

private:
	void convertStringToArray(string s, int** tab, int* size);
	void convertStringToTransitionData(string s, int * from, char * label, int * to);
	string generateAlphabet(int n);
};