#include "charCounter.h"
#include "hTree.h"

#ifndef LF_HTREEMAKER_H
#define LF_HTREEMAKER_H

class hTreeMaker
{
	std::vector<hTree> trees;
	int start;

	public:
	void addTree(const std::string value, int weight) 
	{
		int i;
		bool isset = false;
		hTree temp, temp2;

		for (i = start; i < size(); i++)
		{
			if (!isset)
			{
				if (weight < trees[i].weight())
				{
					temp = trees[i];
					isset = true;
				}
			}
			else
			{
				temp2 = trees[i];
				trees[i] = temp;
				temp = temp2; 
			}
		}
		if (!isset)
		{
			trees.push_back(hTree(value, weight));
		}
		else
		{
			trees.push_back(temp);
		}
	}

	int size() const
	{
		return trees.size() - start;
	}

	const hTree& operator[](int i) const
	{
		return trees[i+start];
	}

	void makeTreesFromCount(const std::string& input)
	{
		int i;
		charCounter cc1;
		char buf[] = "0";

		cc1.countString(input);

		for (i = 0; i < 256; i++)
		{
			buf[0] = i;
			addTree(buf, cc1.getCount((char)i));
		}
	}

	hTreeMaker()
	{
		start = 0;
	}
};

#endif

