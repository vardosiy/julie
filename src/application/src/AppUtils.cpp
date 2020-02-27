#include "AppUtils.hpp"

#include "utils/Utils.hpp"

#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------

std::string readFileContent(std::string_view _filePath)
{
	std::string fileContent;

	std::ifstream file(_filePath.data());
	ASSERTM(file.is_open(), "Can't open file {}", _filePath.data());
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContent = buffer.str();
	}

	return fileContent;
}

//-----------------------------------------------------------------------------
