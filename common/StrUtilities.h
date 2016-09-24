#pragma once
#include <string>
#include <codecvt>

/*convert an 8-bit char string to a wide 16-bit string*/
inline std::wstring to_wchar(const std::string _str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	std::wstring result = convert.from_bytes(_str);
	return result;
}

/*decorate a string with quote
useful when those are sent as string parameters in cmd*/
inline std::string quote(const std::string& _str)
{
	return std::string("\"") + _str + std::string("\"");
}
/*decorate a wstring with quote
useful when those are sent as string parameters in cmd*/
inline std::wstring quote(const std::wstring& _str)
{
	return std::wstring(L"\"") + _str + std::wstring(L"\"");
}

/*generic random 8-bit char*/
inline char rand_char()
{
	return char(rand() % UCHAR_MAX);
}

/*random simple bin string (e.g. 1000101011)*/
inline char rand_simple_bin_char()
{
	static const char sim_bin[] ="01";

	return sim_bin[rand() % (sizeof(sim_bin)-1)];
}

/*random alpha-numeric string*/
inline char rand_alphanum_char()
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	return alphanum[rand() % (sizeof(alphanum)-1)];
}

/*generate a bit mask with only 1 bit set
the index of this bit is returned in the highBit parameter
The function is generric and can be used to generate bit mask of any size (8-bit, 16-bit, 32-bit)*/
template<typename T>
inline T rand_bitMask(int& highBit)
{
	highBit = rand() % (sizeof(T)*8);
	return T(1 << highBit);
}