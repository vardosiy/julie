#pragma once

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
	struct PropertyData
	{
		using UniformValue =
			std::variant<float, int, glm::vec3, glm::vec4, const jl::Texture*, const jl::CubeTexture*>;

		template<typename T>
		PropertyData(const std::string& _name, const T& _val)
			: name(_name)
			, value(_val)
		{
		}

		std::string name;
		UniformValue value;
	};

//-----------------------------------------------------------------------------
	void bind() const;

	const jl::Shader* getShader() const noexcept;
	void setShader(const jl::Shader& _shader) noexcept;

	const std::vector<PropertyData>& getProperties() const noexcept;

	void setProperty(const std::string& _name, float _val) noexcept						{ setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, int _val) noexcept						{ setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, const glm::vec4& _val) noexcept			{ setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, const glm::vec3& _val) noexcept			{ setPropertyCommon(_name, _val); }
	void setProperty(const std::string& _name, const jl::Texture& _val) noexcept		{ setPropertyCommon(_name, &_val); }
	void setProperty(const std::string& _name, const jl::CubeTexture& _val) noexcept	{ setPropertyCommon(_name, &_val); }

//-----------------------------------------------------------------------------
private:
	template<typename T>
	void setPropertyCommon(const std::string& _name, T _val) noexcept;

//-----------------------------------------------------------------------------
	const jl::Shader* m_shader;
	std::vector<PropertyData> m_properties;
};

//-----------------------------------------------------------------------------

template<typename T>
inline void Material::setPropertyCommon(const std::string& _name, T _val) noexcept
{
	auto predicate = [&_name](const PropertyData& _data)
	{
		return _name == _data.name;
	};

	auto it = std::find_if(m_properties.begin(), m_properties.end(), predicate);
	if (it != m_properties.end())
	{
		it->value = _val;
	}
	else
	{
		m_properties.emplace_back(_name, _val);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
