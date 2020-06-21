#include "ui/properties/PropertyTypes.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/Material.hpp"

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
		QString filePath;

		if (_value)
		{
			filePath = ResourceManager::getInstance().findSourceFile(*_value).c_str();
		}

		return QVariant::fromValue(TextureUiWrapper{ filePath, _value });
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
		jl::Material& material = m_material;
		const std::string& propName = m_propName;

		auto editCallback = [&material, &propName](float _val) { material.setProperty(propName, _val); };
		return QVariant::fromValue(FloatValUiWrapper{ _value, editCallback });
	}

	QVariant operator() (jl::s32 _value) const noexcept
	{
		return (*this)(static_cast<float>(_value));
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
