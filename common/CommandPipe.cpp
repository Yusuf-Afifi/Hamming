#include "stdafx.h"
#include "CommandPipe.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "StrUtilities.h"
namespace CommandPipe
{

	std::string execute_str_res(std::string exename, std::string _param1, std::string _param2) {
		char buffer[128];
		std::string command = exename + " " + quote(_param1) + "    " + quote(_param2);
		std::string result = "";
		std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
		if (!pipe) throw std::runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer, 128, pipe.get()) != NULL)
				result += buffer;
		}
		return result;
	}

	int execute(std::string exename, std::string _param1, std::string _param2) {
		char buffer[128];
		std::string command = exename + " " + quote(_param1) + "    " + quote(_param2);
		std::string result = "";
		std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
		if (!pipe) throw std::runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer, 128, pipe.get()) != NULL)
				result += buffer;
		}
		return stoi(result);
	}
}