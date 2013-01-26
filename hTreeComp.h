
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

	std::string decompress(const std::string input)
	{
		int i, start = -1, dsize = 0;
		int mode = 0;
		std::stringstream convert, code;
		bitStream bsi;
		int low = 0; int high = 1000;

		for (i = 0; i < (int)input.size() && start == -1; i++)
		{
			if (mode == 0 && input.c_str()[i] >= '0' && input.c_str()[i] <= '9')
			{
				mode = 1;
			}
			else if (mode == 1 && input.c_str()[i] == ' ')
			{
				mode = 2;
				start = i + 1;
			}
		}

		if (start == -1) { return ""; }

		convert.str(input.substr(0, start));
		convert >> dsize;

		bsi.setData(input.substr(start, input.length()-start));

		for (i = 0; i < dsize; i++)
		{
			code << bsi.get();
			bsi.next();
			comptree.search(low, high, code.str());

			if (i % 8 == 0)
			{
				std::cout << "key: " << code.str();
				std::cout << "\tfound: " << comptree[low].code << std::endl;
				low = 0;
				high = 256;
				code.str("");
			}
		}

		return "";
	}
};

#endif

