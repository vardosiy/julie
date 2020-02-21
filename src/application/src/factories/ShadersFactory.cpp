#include "factories/ShadersFactory.hpp"

#include "renderer/Shader.hpp"

#include "utils/Utils.hpp"

#include <json/json.h>
#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Shader> ShadersFactory::load(std::string_view _filePath)
{
	const std::string document = readFile(_filePath);

	Json::Reader reader;
	Json::Value root;

	std::string vsStr;
	std::string fsStr;

	if (reader.parse(document, root))
	{
		{
			const Json::Value& vsJson = root["vs"];
			if (vsJson.isString())
			{
				vsStr = vsJson.asString();
			}
		}
		{
			const Json::Value& fsJson = root["fs"];
			if (fsJson.isString())
			{
				fsStr = fsJson.asString();
			}
		}
	}

	if (!vsStr.empty() && !fsStr.empty())
	{
		return jl::Shader::create(vsStr, fsStr);
	}
	return nullptr;
}

//-----------------------------------------------------------------------------

//std::unique_ptr<jl::Shader> ShadersFactory::load(std::string_view _vsPath, std::string_view _fsPath)
//{
//	const std::string vsStr = readFile(_vsPath);
//	const std::string fsStr = readFile(_fsPath);
//	return jl::Shader::create(vsStr, fsStr);
//}

//-----------------------------------------------------------------------------

std::string ShadersFactory::readFile(std::string_view _filePath)
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
