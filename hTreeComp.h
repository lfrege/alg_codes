
#include "hTreeMaker.h"
#include "bitStream.h"
#include <sstream>

#ifndef LF_HTREECOMP_H
#define LF_HTREECOMP_H

class hTreeComp
{
	hTree comptree;
	std::vector<std::string> rev;

	public:
	void makeTree(const std::string& input)
	{
		hTreeMaker htm;

		htm.makeTreesFromCount(input);

		comptree = htm[0];

		rev = comptree.buildReverseLookup();
	}

	std::string compress(const std::string& input) const
	{
		int i,j;
		bitStream bso;
		std::string code, output2;
		std::stringstream output1;
		int size = 0;

		for (i = 0; i < (int)input.length(); i++)
		{
			code = rev[charCounter::charIndex(input[i])];
			for (j = 0; j < (int)code.length(); j++)
			{
				if (code[j] == '1')
				{
					bso.set(true);
				}
				else
				{
					bso.set(false);
				}
				size++;
			}
		}

		output1 << " " << size << " ";
		output2.resize(output1.str().length() + bso.data().length() + 1);

		for (i = 0; i < (int)output1.str().length(); i++)
		{
			output2[i] = output1.str()[i];
		}
		for (i = 0; i < (int)bso.data().length(); i++)
		{
			output2[i + output1.str().length()] = bso.data().c_str()[i];
		}
		output2[output2.length() - 1] = '\n';

		return output2;
	}
};

#endif

