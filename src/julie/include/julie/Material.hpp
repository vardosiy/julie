#pragma once

#include "julie/core/Types.hpp"
#include "julie/Entity.hpp"

#include "utils/TypeTraits.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <variant>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Shader;
class Texture;
class CubeTexture;

class Material : public Entity
{
//-----------------------------------------------------------------------------
public:
	struct Property
	{
		using TValue =
			std::variant<float, s32, glm::vec2, glm::vec3, glm::vec4, Texture*, CubeTexture*>;

		std::string name;
		TValue value;
	};

//-----------------------------------------------------------------------------
	const Shader* getShader() const noexcept		{ return m_shader; }
	void setShader(const Shader* _shader) noexcept	{ m_shader = _shader; }

	const std::vector<Property>& getProperties() const noexcept;
	void clearProperties() noexcept;

	template<typename T, typename = std::enable_if_t< utils::VariantHasAlternative_v<T, Property::TValue> >>
	void setProperty(const std::string& _name, const T& _val) noexcept;

//-----------------------------------------------------------------------------
private:
	const Shader* m_shader = nullptr;
	std::vector<Property> m_properties;
};

//-----------------------------------------------------------------------------

template<typename T, typename>
void Material::setProperty(const std::string& _name, const T& _val) noexcept
{
	auto it = std::find_if(m_properties.begin(), m_properties.end(), [&_name](const Property& _property)
	{
		return _name == _property.name;
	});

	if (it != m_properties.end())
	{
		it->value = _val;
	}
	else
	{
		m_properties.emplace_back(Property{ _name, _val });
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
