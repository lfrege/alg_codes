
#include <vector>
#include <algorithm>

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

			return output;
		}

		hTreeRow(const std::string& code1, const std::string value1, int weight1)
		{
			code = code1;
			value = value1;
			weight = weight1;
		}

		bool operator<(const hTreeRow& rhs) const
		{
			return code < rhs.code;
		}

		bool operator==(const hTreeRow& rhs) const
		{
			return code == rhs.code;
		}
	};

	std::vector<hTreeRow> rows;
	int _weight;

	public:
	void sort()
	{
		std::sort(rows.begin(), rows.end());
	}

	std::string search(int&low, int& high, const std::string& key)
	{
		int i;
		int lastlow, lasthigh;
		if (low < 0) { low = 0;}
		if (high >= (int)rows.size()) { high = rows.size() - 1; }
		if (low == high) 
		{
			low = 0;
			high = rows.size() - 1; 
		}

		lastlow = low;
		lasthigh = high;

		while (lastlow != lasthigh && lastlow != lasthigh - 1)
		{
			i = (lastlow + lasthigh) / 2;
			if (key == rows[i].code)
			{
				low = high = i;
				return rows[i].value;
			}
			else if (key < rows[i].code) { lasthigh = i; }
			else if (key > rows[i].code) { lastlow = i; }
			std::cout << "key: " << key  << " low: " << lastlow << "\thigh: "<< lasthigh << "\tcode: " << rows[i].code << std::endl;
		}

		return "";
	}

	std::vector<std::string> buildReverseLookup() const
	{
		int i;
		std::vector<std::string> output;
		output.resize(256);

		for (i = 0; i < (int)rows.size(); i++)
		{
			output[charCounter::charIndex(rows[i].value.c_str()[0])] = rows[i].code;
		}

		return output;
	}

	std::string toString() const
	{
		int i;
		std::string output;

		for (i = 0; i < (int)rows.size(); i++)
		{
			output += rows[i].toString() + "\n";
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

	hTree merge(const hTree& rhs) const
	{
		hTree output;
		int i;
		for (i = 0; i < size(); i++)
		{
			output.leftAdd(rows[i].code, rows[i].value, rows[i].weight);
		}
		for (i = 0; i < rhs.size(); i++)
		{
			output.rightAdd(rhs[i].code, rhs[i].value, rhs[i].weight);
		}
		return output;
	}

	const hTreeRow& operator[](int i) const
	{
		return rows[i];
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

