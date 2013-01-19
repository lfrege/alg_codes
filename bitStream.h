#ifndef LF_BITSTREAM_H
#define LF_BITSTREAM_H



class bitStream
{
	std::string _data;
	int current_byte;
	int current_bit;


	public:

	const std::string& data() const
	{
		return _data;
	}

	int byte() const
	{
		return current_byte;
	}

	int bit() const
	{
		return current_bit;
	}
	
	void start()
	{
		current_bit = 0;
		current_byte = 0;
	}

	void next()
	{
		current_bit++;
		if (current_bit >= 8)
		{
			current_bit %= 8;
			current_byte++;
		}
	}

	bool eof() const
	{
		if (byte() < (int)data().length())
		{
			return false;
		}
		return true;
	}

	bool get() const
	{
		if (eof()) { return false; }

		char ch = data().c_str()[byte()];
		bool outbit = (ch >> bit()) & 1;

		return outbit;
	}

	void setData(const std::string& input)
	{
		_data = input;
	}
};



#endif

