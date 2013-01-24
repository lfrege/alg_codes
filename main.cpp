#include <iostream>
#include "hTreeMaker.h"
#include "bitStream.h"
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
	hTreeMaker htm;

	if (argc < 2)
	{
		cerr << "Error: please supply a file name" << endl;
		return -1;
	}

	readAll(argv[1], a);

	htm.makeTreesFromCount(a);

	cerr << "htm size: " << htm.size() << endl;

	cout << htm[0].toString();

	return 0;
}
