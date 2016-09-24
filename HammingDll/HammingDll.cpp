#include "HammingDll.h"
#include <sstream>

HAMMINGDLL_API int Hamming_dist_char(const std::string& A, const std::string& B)
{
	return Hamming_dist_sym_Itr(A.begin(), A.end(), B.begin(), B.end());
}

HAMMINGDLL_API int Hamming_dist_bin(const std::string& A, const std::string& B)
{
	return Hamming_dist_bin_Itr(A.begin(), A.end(), B.begin(), B.end());
}

//HAMMINGDLL_API std::string bin_print(const std::string& A)
//{
//	std::ostringstream os;
//	std::vector<bool> bitArr_A;
//	fill_bitArr(A, bitArr_A);
//	for (size_t i = 0, sz = bitArr_A.size(); i < sz; i++)
//	{
//		os << bitArr_A[i] ? 1 : 0;
//	}
//	return os.str();
//}
