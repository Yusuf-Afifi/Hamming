#include "stdafx.h"
#include "RandomString.h"
#include "StrUtilities.h"
#include <set>
#include <fstream>
namespace RandomString
{
	std::string generate(size_t _length, size_t _upper_limit)
	{
		if (_length == 0)
			_length = 1 + rand() % _upper_limit;
		std::string result;
		result.resize(_length);

		for (size_t i = 0; i < _length; i++)
		{
			result[i] = rand_simple_bin_char();
		}

		return result;
	}

	int alter(std::string& _str, size_t _modCount)
	{
		size_t sz = _str.size();

		_modCount = _modCount >= sz ? sz - 1 : _modCount;

		if (_modCount == 0)
			_modCount = rand() % sz;

		std::set<int> uniqueness_set;

		for (size_t i = 0; i < _modCount; i++)
		{
			int mod_char_idx = rand() % sz;

			if (uniqueness_set.find(mod_char_idx) == uniqueness_set.end())
			{
				char& mod_number = _str[mod_char_idx];
				char r_char = rand_simple_bin_char();
				if (r_char != mod_number)
				{
					mod_number = r_char;
					uniqueness_set.insert(mod_char_idx);
				}
			}
		}

		return uniqueness_set.size();
	}
	
	
};

namespace RandomBlob
{
	std::string generate(size_t _length, size_t _upper_limit)
	{
		if (_length == 0)
			_length = 1 + rand() % _upper_limit;
		std::string result;
		result.resize(_length);

		for (size_t i = 0; i < _length; i++)
		{
			result[i] = rand_char();
		}

		return result;
	}

	int alter(std::string& _str, size_t _modCount)
	{
		size_t sz = _str.size();

		_modCount = _modCount >= sz ? sz - 1 : _modCount;

		if (_modCount == 0)
			_modCount = rand() % sz;

		std::set<int> uniqueness_set;

		for (size_t i = 0; i < _modCount; i++)
		{
			int mod_char_idx = rand() % sz;
			int highBit;
			auto r_mask = rand_bitMask<char>(highBit);
			int uid = mod_char_idx * highBit + r_mask; // uid for the modified bit

			if (uniqueness_set.find(uid) == uniqueness_set.end())
			{
				char& mod_number = _str[mod_char_idx];
				mod_number ^= r_mask; //xor to alter a single bit
				uniqueness_set.insert(uid);

			}
		}

		return uniqueness_set.size();
	}

	std::vector<int> generate_int(size_t _length, size_t _upper_limit)
	{
		if (_length == 0)
			_length = 1 + rand() % _upper_limit;
		std::vector<int> result;
		result.resize(_length);

		for (size_t i = 0; i < _length; i++)
		{
			result[i] = rand();
		}

		return result;
	}

	int alter_int(std::vector<int>& _str, size_t _modCount)
	{
		size_t sz = _str.size();

		_modCount = _modCount >= sz ? sz - 1 : _modCount;

		if (_modCount == 0)
			_modCount = rand() % sz;

		std::set<int> uniqueness_set;

		for (size_t i = 0; i < _modCount; i++)
		{
			int mod_char_idx = rand() % sz;
			int highBit;
			auto r_mask = rand_bitMask<int>(highBit);
			int uid = mod_char_idx * highBit + r_mask; // uid for the modified bit

			if (uniqueness_set.find(uid) == uniqueness_set.end())
			{
				int& mod_number = _str[mod_char_idx];
				mod_number ^= r_mask; //xor to alter a single bit
				uniqueness_set.insert(uid);

			}
		}

		return uniqueness_set.size();
	}

	void save(const std::string& _str, const char* _filename)
	{
		std::ofstream output(_filename, std::ios::binary | std::ios_base::trunc);
		std::copy(_str.begin(), _str.end(), std::ostreambuf_iterator<char>(output));
	}
};
