
#include <vector>

#ifndef LF_HTREE_H
#define LF_HTREE_H

class hTree
{
	class hTreeRow
	{
		public:
		std::string code;
		std::string value;
		int weight;

		std::string toString() const
		{
			std::string output;
			output = code + "\t";
			output += value + "\t";
			output += weight;
		}

		hTreeRow(const std::string& code, const std::string value1, int weight1)
		{
			code = code1;
			value = value1;
			weight = weight1;
		}
	};

	std::vector<hTreeRow> rows;
	int _weight;

	public:
	std::string toString() const
	{
		int i;
		std::string output;

		for (i = 0; i < (int)rows.size(); i++)
		{
			output += rows[i].toString();
		}

		return output;
	}

	int size() const
	{
		return rows.size();
	}

	int weight() const
	{
		return _weight;
	}

	void leftAdd(const std::string code, const std::string value, int weight)
	{
		rows.push_back(hTreeRow("1" + code, value, weight));
		_weight += weight;
	}

	void rightAdd(const std::string code, const std::string value, int weight)
	{
		rows.push_back(hTreeRow("0" + code, value, weight));
		_weight += weight;
	}

	hTree(const std::string input, int inweight)
	{
		rows.push_back(hTreeRow("", input, inweight));
		_weight = inweight;
	}

	hTree()
	{
		_weight = 0;
	}
};


#endif


