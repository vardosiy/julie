#pragma once

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {
class Model;
}

class ModelsFactory
{
public:
	static std::unique_ptr<jl::Model> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<jl::Model> createRect();
};

//-----------------------------------------------------------------------------
