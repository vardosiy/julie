#pragma once

#include <string_view>
#include <memory>
#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;

class ModelCreationHelper
{
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath);
	static std::vector<std::unique_ptr<Model>> load(std::string_view _filePath);

private:
	static std::unique_ptr<Model> loadNfg(std::string_view _filePath);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
