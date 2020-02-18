#pragma once

#include "data/DataEntity.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <variant>

//-----------------------------------------------------------------------------

namespace jl {
class Shader;
class Texture;
class CubeTexture;
}

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class Material : public DataEntity
{
public:
	Material(std::string _name);
	~Material();

	void bind() const;

	const jl::Shader* getShader() const noexcept;
	void setShader(const jl::Shader& _shader) noexcept;

	void setProperty(std::string _name, float _val)						{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, int _val)						{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, const glm::vec4& _val)			{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, const glm::vec3& _val)			{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, const jl::Texture& _val)		{ m_propertiesData.emplace_back(std::move(_name), &_val); }
	void setProperty(std::string _name, const jl::CubeTexture& _val)	{ m_propertiesData.emplace_back(std::move(_name), &_val); }

private:
	struct PropertyData
	{
		using UniformValue =
			std::variant<float, int, glm::vec3, glm::vec4, const jl::Texture*, const jl::CubeTexture*>;

		template<typename T>
		PropertyData(std::string _name, const T& _val)
			: name(std::move(_name))
			, value(_val)
		{
		}

		std::string name;
		UniformValue value;
	};

private:
	const jl::Shader* m_shader;
	std::vector<PropertyData> m_propertiesData;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
