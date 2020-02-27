#include "factories/ShadersFactory.hpp"
#include "AppUtils.hpp"

#include "renderer/Shader.hpp"

#include "utils/Utils.hpp"

#include <json/json.h>
#include <fstream>

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Shader> ShadersFactory::loadFromFile(std::string_view _filePath)
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
		return jl::Shader::create(vsStr, fsStr);
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Shader> ShadersFactory::loadFromSeparateFiles(std::string_view _vsPath, std::string_view _fsPath)
{
	const std::string vsStr = readFileContent(_vsPath);
	const std::string fsStr = readFileContent(_fsPath);
	return jl::Shader::create(vsStr, fsStr);
}

//-----------------------------------------------------------------------------
