#include "ui/props/PropertyTypes.hpp"
#include "renderer/Material.hpp"

#include "utils/Utils.hpp"

#include <QVariant>

class MaterialPropertyValueVisitor
{
public:
	MaterialPropertyValueVisitor(jl::Material& _material, const std::string& _propName)
		: m_material(_material)
		, m_propName(_propName)
	{
	}

	QVariant operator() (const jl::Texture* _value) const noexcept
	{
		return QVariant::fromValue(TextureUiWrapper{ _value });
	}

	QVariant operator() (const glm::vec3& _value) const noexcept
	{
		jl::Material& material = m_material;
		const std::string& propName = m_propName;

		auto editCallback = [&material, &propName](const glm::vec3& _val) { material.setProperty(propName, _val); };
		return QVariant::fromValue(ColorUiWrapper{ _value, editCallback });
	}

	QVariant operator() (float _value) const noexcept
	{
		return QVariant(_value);
	}

	template<typename T>
	QVariant operator() (const T& _value) const noexcept
	{
		ASSERT(0);
		return QVariant();
	}

private:
	jl::Material& m_material;
	const std::string& m_propName;
};
