#pragma once

#include <iostream>
#include <string>
#include "Automate.h"

class AutomateFileParser
{

private:
	bool isDebugged = false;

public:
	AutomateFileParser();
	void loadFile(string path);
	Automate& generate();

	string getAlphabet();
	// ...

	void setDebugged(bool b);
};