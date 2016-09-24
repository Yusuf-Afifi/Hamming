#pragma once
#include <string>

namespace CommandPipe
{
	/* run a command and fetch the stdout as a string
	params:
	//** exename **\\
	the command to execute 
	//** _param1, _param2 **\\
	optional parameters that will be decorated with douyble quotes
	return:
	The stdout of the command
	*/
	std::string execute_str_res(std::string exename, std::string _param1, std::string _param2);

	/* run a command and fetch the stdout as an integer
	params:
	//** exename **\\
	the command to execute
	//** _param1, _param2 **\\
	optional parameters that will be decorated with douyble quotes
	return:
	A parsed integer of the stdout of the command
	Exceptions:
	If the process produces a non-integer string an exception of type std::invalid_argument
	*/
	int execute(std::string exename, std::string _param1, std::string _param2);
}