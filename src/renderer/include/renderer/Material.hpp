#pragma once

#include "renderer/Types.hpp"

#include <boost/noncopyable.hpp>
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

class Material : boost::noncopyable
{
//-----------------------------------------------------------------------------
public:
	struct Property
	{
		using TValue =
			std::variant<float, s32, glm::vec2, glm::vec3, glm::vec4, const jl::Texture*, const jl::CubeTexture*>;

		std::string name;
		TValue value;
	};

//-----------------------------------------------------------------------------
	void bind() const;

	const jl::Shader* getShader() const noexcept;
	void setShader(const jl::Shader& _shader) noexcept;

	const std::vector<Property>& getProperties() const noexcept;

	void setProperty(const std::string& _name, float					_val) noexcept { setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, s32						_val) noexcept { setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, glm::vec2				_val) noexcept { setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, glm::vec3				_val) noexcept { setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, glm::vec4				_val) noexcept { setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, const jl::Texture&		_val) noexcept { setPropertyCommon(_name, &_val); }
	void setProperty(const std::string& _name, const jl::CubeTexture&	_val) noexcept { setPropertyCommon(_name, &_val); }

//-----------------------------------------------------------------------------
private:
	template<typename T>
	void setPropertyCommon(const std::string& _name, T _val) noexcept;

//-----------------------------------------------------------------------------
	const jl::Shader* m_shader;
	std::vector<Property> m_properties;
};

//-----------------------------------------------------------------------------

template<typename T>
inline void Material::setPropertyCommon(const std::string& _name, T _val) noexcept
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
