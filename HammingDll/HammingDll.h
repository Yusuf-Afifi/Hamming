#ifdef HAMMINGDLL_EXPORTS
#define HAMMINGDLL_API __declspec(dllexport)
#else
#define HAMMINGDLL_API __declspec(dllimport)
#endif

#include <string>


/* symbol-based generic hamming distance calculator 
params:
//** beginA, endA **\\
start and end iterators of the first container A
//** beginB, endB **\\
start and end iterators of the second container B
return:
The hamming distance. The number of differnt symbols. Symbols can be (char, int , short etc.).
The result is -1 if the iterators point to collections of different lengths
*/
template <class Itrator>
int Hamming_dist_sym_Itr(Itrator beginA, Itrator endA, Itrator beginB, Itrator endB)
{
	if ((endA - beginA) != (endB - beginB))
		return -1;
	int hamming_distance = 0;
	for (Itrator itr_a = beginA, itr_b = beginB; itr_a != endA; ++itr_a, ++itr_b)
	{
		auto a = *itr_a;
		auto b = *itr_b;

		if (a != b)
		{
			hamming_distance++;
		}
	}
	return hamming_distance;
}

/* binary generic hamming distance calculator
params:
//** beginA, endA **\\
start and end iterators of the first container A
//** beginB, endB **\\
start and end iterators of the second container B
return:
The hamming distance. The number of differnt bits between the two containers
The result is -1 if the iterators point to collections of different lengths
*/
template <class Itrator>
int Hamming_dist_bin_Itr(Itrator beginA, Itrator endA, Itrator beginB, Itrator endB)
{
	if ((endA - beginA) != (endB - beginB))
		return -1;
	int hamming_distance = 0;
	for (Itrator itr_a = beginA, itr_b = beginB; itr_a != endA; ++itr_a, ++itr_b)
	{
		auto a = *itr_a;
		auto b = *itr_b;

		int element_size = sizeof(a)*8;
		// optimize for byte arrays
		if (element_size == 8)
		{
			if ((a & 0x01) != (b & 0x01)) hamming_distance++;
			if ((a & 0x02) != (b & 0x02)) hamming_distance++;
			if ((a & 0x04) != (b & 0x04)) hamming_distance++;
			if ((a & 0x08) != (b & 0x08)) hamming_distance++;
			if ((a & 0x10) != (b & 0x10)) hamming_distance++;
			if ((a & 0x20) != (b & 0x20)) hamming_distance++;
			if ((a & 0x40) != (b & 0x40)) hamming_distance++;
			if ((a & 0x80) != (b & 0x80)) hamming_distance++;
		}
		else
		{
			// will work for non-byter arrays
			for (int i = 0; i < element_size; i++)
			{
				if ((a & (0x01 << i)) != (b & (0x01 << i))) hamming_distance++;
			}
		}

	}
	return hamming_distance;
}

/*
string version of the generic symbol hamming function for ease of use with strings. Symbol = char
*/
HAMMINGDLL_API int Hamming_dist_char(const std::string& A, const std::string& B);

/*
string version of the generic binary hamming function for ease of use with strings.
*/
HAMMINGDLL_API int Hamming_dist_bin(const std::string& A, const std::string& B);
