#pragma once

#include "utils/Singleton.hpp"

#include <map>
#include <functional>
#include <memory>

namespace jl {
class Material;
}

class MaterialsManager : public utils::Singleton<MaterialsManager>
{
	friend class utils::Singleton<MaterialsManager>;

//-----------------------------------------------------------------------------
public:
	void clear() noexcept;

	jl::Material& createMaterial(const std::string& _name) noexcept;
	jl::Material* findMaterial(const std::string& _name) const noexcept;

	void deleteMaterial(const std::string& _name) noexcept;
	void deleteMaterial(jl::Material& _material) noexcept;

	std::string findMaterialName(const jl::Material& _material) const noexcept;

	void forEachMaterial(const std::function<void(const std::string&, jl::Material&)>& _callback);
	void forEachMaterial(const std::function<void(const std::string&, const jl::Material&)>& _callback) const;

//-----------------------------------------------------------------------------
private:
	MaterialsManager() = default;
	~MaterialsManager() = default;

//-----------------------------------------------------------------------------
	using MaterialsMap = std::map<std::string, std::unique_ptr<jl::Material>>;
	MaterialsMap m_materials;
};
