#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;

class ModelsFactory
{
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<Model> createRect(const glm::vec3 & _pos, const glm::vec2 & _size); // _pos => bottom-left coord
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
