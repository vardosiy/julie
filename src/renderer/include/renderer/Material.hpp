#pragma once

#include "renderer/Types.hpp"

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

class Material
{
public:
	void bind() const;

	void setShader(const Shader & _shader) noexcept;

	const Shader * getShader() const noexcept { return m_shader; }

	void setProperty(const std::string & _name, float _val)					{ m_propertiesData.emplace_back(_name, _val); }
	void setProperty(const std::string & _name, s32 _val)					{ m_propertiesData.emplace_back(_name, _val); }
	void setProperty(const std::string & _name, const glm::vec4 & _val)		{ m_propertiesData.emplace_back(_name, _val); }
	void setProperty(const std::string & _name, const glm::vec3 & _val)		{ m_propertiesData.emplace_back(_name, _val); }
	void setProperty(const std::string & _name, const Texture & _val)		{ m_propertiesData.emplace_back(_name, &_val); }
	void setProperty(const std::string & _name, const CubeTexture & _val)	{ m_propertiesData.emplace_back(_name, &_val); }

private:
	struct PropertyData
	{
		using UniformValue =
			std::variant<float, s32, glm::vec3, glm::vec4, const Texture *, const CubeTexture *>;

		template<typename T>
		PropertyData(const std::string & _name, const T & _val)
			: name(_name)
			, value(_val)
		{
		}

		std::string name;
		UniformValue value;
	};

	const Shader * m_shader = nullptr;
	std::vector<PropertyData> m_propertiesData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
