#pragma once

#include "utils/Singleton.hpp"

#include <functional>
#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;

class MaterialsManager : public utils::Singleton<MaterialsManager>
{
	friend class utils::Singleton<MaterialsManager>;

//-----------------------------------------------------------------------------
public:
	void clear() noexcept;

	size_t getMaterialsCount() const noexcept;

	Material& createMaterial(const std::string& _name) noexcept;
	Material* findMaterial(const std::string& _name) const noexcept;

	void deleteMaterial(const std::string& _name) noexcept;
	void deleteMaterial(const Material& _material) noexcept;

	void forEachMaterial(const std::function<void(Material&)>& _callback);
	void forEachMaterial(const std::function<void(const Material&)>& _callback) const;

//-----------------------------------------------------------------------------
private:
	MaterialsManager() = default;
	~MaterialsManager() = default;

//-----------------------------------------------------------------------------
	std::vector<std::unique_ptr<Material>> m_materials;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
