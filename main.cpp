#include <iostream>
#include "hTreeComp.h"
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
	string a,b;
	hTreeComp htc;

	if (argc < 3)
	{
		cerr << "Error: please supply a file name" << endl;
		return -1;
	}

	readAll("main.cpp", b);
	readAll(argv[2], a);

	htc.makeTree(b);

	if (argv[1][0] == 'd')
	{
		cout << htc.decompress(a);
	}
	else
	{
		cout << htc.compress(a);
	}


	return 0;
}
