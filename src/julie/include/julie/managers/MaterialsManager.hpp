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

	size_t getMaterialsCount() const noexcept;

	jl::Material& createMaterial(const std::string& _name) noexcept;
	jl::Material* findMaterial(const std::string& _name) const noexcept;

	void deleteMaterial(const std::string& _name) noexcept;
	void deleteMaterial(const jl::Material& _material) noexcept;

	void forEachMaterial(const std::function<void(jl::Material&)>& _callback);
	void forEachMaterial(const std::function<void(const jl::Material&)>& _callback) const;

//-----------------------------------------------------------------------------
private:
	MaterialsManager() = default;
	~MaterialsManager() = default;

//-----------------------------------------------------------------------------
	std::vector<std::unique_ptr<jl::Material>> m_materials;
};
