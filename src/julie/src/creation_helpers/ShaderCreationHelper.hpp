#pragma once

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

class Shader;

class ShaderCreationHelper
{
public:
	static std::unique_ptr<Shader> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<Shader> loadFromFiles(std::string_view _vsPath, std::string_view _fsPath);

private:
	static std::string readFileContent(std::string_view _filePath);
};

} // namespace jl

//-----------------------------------------------------------------------------
