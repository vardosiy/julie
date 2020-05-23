#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

namespace jl {
class Material;
class Shader;
}

class MaterialsManager : public utils::Singleton<MaterialsManager>
{
	friend class utils::Singleton<MaterialsManager>;

//-----------------------------------------------------------------------------
public:
	void clear() noexcept;

	jl::Material& getDefaultMaterial() const noexcept;
	jl::Material& createMaterial(const std::string& _name) noexcept;
	jl::Material* findMaterial(const std::string& _name) const noexcept;

	void deleteMaterial(const std::string& _name) noexcept;
	void deleteMaterial(jl::Material& _material) noexcept;

	const std::string& findMaterialName(const jl::Material& _material) const noexcept;

	void forEachMaterial(const std::function<void(const std::string&, jl::Material&)>& _callback);

//-----------------------------------------------------------------------------
private:
	MaterialsManager();
	~MaterialsManager();

//-----------------------------------------------------------------------------
	using MaterialsMap = std::unordered_map<std::string, std::unique_ptr<jl::Material>>;
	MaterialsMap m_materials;

	std::unique_ptr<jl::Shader> m_defaultMaterialShader;

	static const std::string k_defaultMaterialName;
};
