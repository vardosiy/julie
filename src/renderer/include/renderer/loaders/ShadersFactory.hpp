#pragma once

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Shader;

class ShadersFactory
{
public:
	//static std::unique_ptr<Shader> load(std::string_view _filePath);
	static std::unique_ptr<Shader> load(std::string_view _vsPath, std::string_view _fsPath);

private:
	static std::string readShaderFile(std::string_view _filePath);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
