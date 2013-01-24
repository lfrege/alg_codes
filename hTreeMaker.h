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
		addTree(hTree(value, weight)); 
	}

	void addTree(const hTree& input) 
	{
		int i;
		int weight = input.weight();
		bool isset = false;
		hTree temp, temp2;

		for (i = 0; i < size(); i++)
		{
			if (!isset)
			{
				if (weight < trees[start+i].weight())
				{
					temp = trees[start+i];
					trees[start+i] = input;
					isset = true;
				}
			}
			else
			{
				temp2 = trees[start+i];
				trees[start+i] = temp;
				temp = temp2; 
			}
		}
		if (!isset)
		{
			trees.push_back(input);
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

	void reduceTreeList()
	{
		hTree temp;
		while (size() > 1)
		{
			temp = trees[start].merge(trees[start+1]);
			start+=2;
			addTree(temp);
		}
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

		reduceTreeList();
	}

	hTreeMaker()
	{
		start = 0;
	}
};

#endif

