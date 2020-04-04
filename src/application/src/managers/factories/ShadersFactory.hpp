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
	static std::unique_ptr<jl::Shader> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<jl::Shader> loadFromSeparateFiles(std::string_view _vsPath, std::string_view _fsPath);
};

//-----------------------------------------------------------------------------
