#pragma once

#include "data/DataEntity.hpp"
#include "renderer/Material.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <variant>

//-----------------------------------------------------------------------------

namespace jl {
class Material;
}

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class Material : public DataEntity
{
public:
	Material(std::string _name);
	~Material();

	const jl::Material& getMaterial() const noexcept;

	void setShader(std::string _val);
	void setTexture(std::string _propertyName, std::string _val);

	void setProperty(std::string _name, float _val)				{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, int _val)				{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, const glm::vec4& _val)	{ m_propertiesData.emplace_back(std::move(_name), _val); }
	void setProperty(std::string _name, const glm::vec3& _val)	{ m_propertiesData.emplace_back(std::move(_name), _val); }

private:
	struct PropertyData
	{
		using UniformValue =
			std::variant<float, int, glm::vec3, glm::vec4, std::string>;

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
	std::string m_shader;
	jl::Material m_material;

	std::vector<PropertyData> m_propertiesData;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
