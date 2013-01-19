#include <vector>

#ifndef LF_CHARCOUNTER_H
#define LF_CHARCOUNTER_H


class charCounter
{
	std::vector<int> counts;

	static int charIndex(char ch)
	{
		unsigned char ch2 = ch;
		int m = (int) ch2;

		return m;
	}

	void inc(char ch)
	{
		counts[charIndex(ch)]++;
	}

	public:
	void countString(const std::string& input)
	{
		int i;
		for (i = 0; i < (int)input.length(); i++)
		{
			inc(input.c_str()[i]);
		}
	}

	int getCount(char ch) const
	{
		return counts[charIndex(ch)];
	}

	charCounter()
	{
		int i;
		counts.resize(256);
		for (i = 0; i < 256; i++)
		{
			counts[i] = 0;
		}
	}
};

std::ostream& operator<<(std::ostream& lhs,  const charCounter& rhs)
{
	int i;

	for (i = 0; i < 256; i ++)
	{
		lhs << i << "\t" << rhs.getCount(i) << std::endl;
	}

	return lhs;
}


#endif
