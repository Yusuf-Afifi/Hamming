#pragma once
#include <string>
#include <vector>

/*
* RandomString namespace contains functions that assist in generating random strings
*/
namespace RandomString
{
	/* generates a string of size (_length) random alpha numeric (or simple binary) characters 
	params:
	//** _length **\\
	The requested length of the string. The default value is 0.
	If value of 0 is sent then the size of the string will be random.
	//** _upper_limit **\\
	The max size of the generated string, only used when _length== 0.
	*/
	std::string generate(size_t _length = 0, size_t _upper_limit = 1000);

	/* alters random characters in the string with alpha numeric (or simple binary) characters 
	params:
	//** _str **\\
	A reference to the string to be altered
	//** _modCount **\\
	The number of characters to modify. The default value is 0.
	If value of 0 is sent then the number of altered characters in the string will be random.
	return:
	The number of characters that were modified, if  _modCount != 0 then the return will be less than or equal to _modCount
	*/
	int alter(std::string& _str, size_t _modCount = 0);
};


/*
*RandomBlob namespace contains functions that assist in generating random binary objects ... encoded in strings or vectors
*/

namespace RandomBlob
{
	/* generates a string of size (_length) random characters
	params:
	//** _length **\\
	The requested length of the string. The default value is 0.
	If value of 0 is sent then the size of the string will be random.
	//** _upper_limit **\\
	The max size of the generated string, only used when _length== 0.
	*/
	std::string generate(size_t _length = 0, size_t _upper_limit = 1000);

	/* an integer version of the generate function in order to expand testing covarage*/
	std::vector<int> generate_int(size_t _length = 0, size_t _upper_limit = 1000);
	/* alters random bits in the string
	params:
	//** _str **\\
	A reference to the string to be altered
	//** _modCount **\\
	The number of bits to modify. The default value is 0.
	If value of 0 is sent then the number of altered bits in the string will be random.
	return:
	The number of bits that were modified, if  _modCount != 0 then the return will be less than or equal to _modCount
	*/
	int alter(std::string& _str, size_t _modCount = 0);

	/* an integer version of the alter function in order to expand testing covarage*/
	int alter_int(std::vector<int>& _str, size_t _modCount = 0);
	/* saves the blob bytes to hard disk
	params:
	//** _str **\\
	A reference to the string to be saved
	//** _filename **\\
	The name of the file to be saved to, if the file already exists, it will be overwritten
	*/
	void save(const std::string& _str, const char* _filename);
};

