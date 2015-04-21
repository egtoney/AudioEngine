//============================================================================
// Name        : AudioEngine.cpp
// Author      : Ethan Toney
// Version     : v1.0
// Copyright   : GNU GENERAL PUBLIC LICENSE Version 2
//					Please see LICENSE for a more detailed description of the license
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string line;
	ifstream myfile ("resources/Tenebrous.mp3");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			for(int i=0 ; i<line.length() ; i++){
				unsigned char c = line[i];
				unsigned int hex = (unsigned int) c;
				cout << hex << " ";
			}
			cout << '\n';
		}
		myfile.close();
	}

	return 0;
}
