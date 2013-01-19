#include <iostream>
#include "charCounter.h"
#include <fstream>

using namespace std;

bool readAll(const string& filename, string& output)
{
	char ch;
	ifstream ifs;
	ifs.open(filename.c_str(), ios::binary);

	if (ifs.is_open())
	{
		do
		{
			ifs.get(ch);
			if (!ifs.eof() && !ifs.bad()) {output += ch;}
		} while(!ifs.eof() && !ifs.bad());

		return true;
	}
	else
	{
		cerr << "Error: could not read from file: " << filename << endl;
		return false;
	}
}

int main(int argc, char **argv)
{
	string a;
	charCounter cc1;

	if (!readAll(argv[1],a))
	{
		cerr << "Error: could not read file." << endl;
	}


	cc1.countString(a);
	cout << cc1 << endl;
	return 0;
}
