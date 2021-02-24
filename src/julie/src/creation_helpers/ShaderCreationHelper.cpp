#include "creation_helpers/ShaderCreationHelper.hpp"

#include "julie/Shader.hpp"

#include "utils/Utils.hpp"

#include <json/json.h>
#include <fstream>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

std::unique_ptr<Shader> ShaderCreationHelper::loadFromFile(std::string_view _filePath)
{
	std::string vsStr;
	std::string fsStr;

	std::ifstream file(_filePath.data());
	ASSERTM(file.is_open(), "Can't open file {}", _filePath.data());
	if (file.is_open())
	{
		Json::CharReaderBuilder readerBuilder;
		readerBuilder["collectComments"] = false;
		std::string errors;

		Json::Value root;
		if (Json::parseFromStream(readerBuilder, file, &root, &errors))
		{
			const Json::Value& vsJson = root["vs"];
			if (vsJson.isString())
			{
				vsStr = vsJson.asString();
			}
			const Json::Value& fsJson = root["fs"];
			if (fsJson.isString())
			{
				fsStr = fsJson.asString();
			}
		}
	}

	ASSERTM(!vsStr.empty() && !fsStr.empty(), "Invalid shaders Json");
	if (!vsStr.empty() && !fsStr.empty())
	{
		return Shader::create(vsStr, fsStr);
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> ShaderCreationHelper::loadFromFiles(std::string_view _vsPath, std::string_view _fsPath)
{
	const std::string vsStr = readFileContent(_vsPath);
	const std::string fsStr = readFileContent(_fsPath);
	return Shader::create(vsStr, fsStr);
}

//-----------------------------------------------------------------------------

std::string ShaderCreationHelper::readFileContent(std::string_view _filePath)
{
	std::string fileContent;

	std::ifstream file(_filePath.data());
	ASSERTM(file.is_open(), "Can't open file {}", _filePath.data());
	if (file.is_open())
	{
		std::getline(file, fileContent, '\0');
	}

	return fileContent;
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
