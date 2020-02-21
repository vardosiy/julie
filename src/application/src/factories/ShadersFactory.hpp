#pragma once

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {
class Shader;
}

class ShadersFactory
{
public:
	static std::unique_ptr<jl::Shader> load(std::string_view _filePath);
	//static std::unique_ptr<jl::Shader> load(std::string_view _vsPath, std::string_view _fsPath);

private:
	static std::string readFile(std::string_view _filePath);
};

//-----------------------------------------------------------------------------
