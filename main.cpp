#include <iostream>
#include "charCounter.h"
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
	int i = 0;
	string a;
	charCounter cc1;
	bitStream bs1, bs2;

	bs1.setData("A0a");

	for (bs1.start(); !bs1.eof(); bs1.next())
	{
		cout << bs1.get();
		bs2.set(bs1.get());
		i++;

		if (i % 8 == 0)
		{
			cout << endl;
		}
	}

	cout << endl << bs2.data() << endl;


	return 0;
}
