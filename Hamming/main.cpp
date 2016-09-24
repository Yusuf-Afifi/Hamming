#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "..\HammingDll\HammingDll.h"

/*true  --> calculate hamming distance on a bit per bit basis (1-bit symbol)*/
/*false --> calculate hamming distance on a char basis (8-bit symbole)*/
bool BINARY_MODE = false; 

/*true  --> the string inputed refer to files to be opened for reading*/
/*false --> the strings inputed are used directly as is*/
bool FILE_MODE = false; 

/*parse the command line and extract parameters

param : "-binary" /"-bin" (optinal)
 specifies that the binary hamming distance will be calculated. 
 if this option is not present then symbol-based (char) hamming distance will be used 

param : "-file" (optinal)
  use this option if the parameters sent will be used as file names. The files will be opened and the hamming distance will be calculated for the contents

free params :
2 strings (A, B respectively) that will be used for the hamming distance calculation or as file names that contain the blobs that will be used for the hamming distance calculation

if the number of free parameters is less than 2, the program will fail.
if the number of free parameters is more than 2, the program will issue a warning but will use the first 2 strings as A, B respectively.

*/
bool parseCommandLine(std::vector<char*> _args, std::string& A, std::string& B)
{
	for (size_t i = 0; i < _args.size(); i++)
	{
		char* curArg = _args[i];

		if (curArg[0] == '-')
		{
			_args.erase(_args.begin() + i--); //erase and adjust iterating var

			if (std::string(curArg) == "-binary" || std::string(curArg) == "-bin")
			{
				BINARY_MODE = true;
			}
			else if (std::string(curArg) == "-file")
			{
				FILE_MODE = true;
			}

		}
	}

	if (_args.size() < 2)
	{
		std::cout << "not enough parameters provided ... exiting" << std::endl;
		return false;
	}
	else if (_args.size() > 2)
	{
		std::cout << "too many parameters provided ... ignoring extra parameters" << std::endl;
	}

	if (FILE_MODE)
	{
		const char* filenameA = _args[0];
		const char* filenameB = _args[1];

		std::ifstream inputA(filenameA, std::ios::binary);
		std::ifstream inputB(filenameB, std::ios::binary);

		if (inputA.bad() || inputB.bad() || !inputA.is_open() || !inputB.is_open())
		{
			std::cout << "error opening one or both files provided ... exiting" << std::endl;
			return false;
		}

		//***** read file directly into memory .... small sized file assumed
		//****** for large file the files need to stay opened and iterators used
		A = std::string(std::istreambuf_iterator<char>(inputA), std::istreambuf_iterator<char>());
		B = std::string(std::istreambuf_iterator<char>(inputB), std::istreambuf_iterator<char>());
	}
	else
	{
		A = _args[0];
		B = _args[1];
	}
	return true;
}

int main(int argc, char *argv[]) 
{  
	std::vector<char*>args (argv + 1, argv + argc);

	std::string A, B;
	if (parseCommandLine(args, A, B))
	{
		int hamming_distance = BINARY_MODE ? Hamming_dist_bin(A, B): Hamming_dist_char(A, B);

		if (hamming_distance < 0)
		{
			std::cout << "Error, strings are different in length ... exiting" << std::endl;
			return 1;
		}

		std::cout << hamming_distance << std::endl;
		return 0;
	}
	return 1;
}