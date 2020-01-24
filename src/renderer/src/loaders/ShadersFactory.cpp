#include "renderer/loaders/ShadersFactory.hpp"

#include "renderer/Types.hpp"
#include "renderer/Shader.hpp"

#include "utils/Assert.hpp"

#include <fstream>
#include <sstream>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

//std::unique_ptr<Shader> ShadersFactory::load(std::string_view _filePath)
//{
//	return nullptr;
//}

//-----------------------------------------------------------------------------

std::unique_ptr<Shader> ShadersFactory::load(std::string_view _vsPath, std::string_view _fsPath)
{
	const std::string vsSource = readShaderFile(_vsPath);
	const std::string fsSource = readShaderFile(_fsPath);
	return Shader::create(vsSource, fsSource);
}

//-----------------------------------------------------------------------------

std::string ShadersFactory::readShaderFile(std::string_view _filePath)
{
	std::string fileContent;

	std::ifstream file(_filePath.data(), std::ios::in);
	ASSERTM(file.is_open(), "Can't open shader file {}", _filePath.data());
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		fileContent = buffer.str();
	}

	return fileContent;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
