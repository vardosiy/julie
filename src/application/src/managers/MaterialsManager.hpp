#pragma once

#include "utils/Singleton.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

namespace jl {
class Material;
}

class MaterialsManager : public utils::Singleton<MaterialsManager>
{
	friend class utils::Singleton<MaterialsManager>;

public:
	void clear() noexcept;

	jl::Material& createMaterial(const std::string& _name) noexcept;
	jl::Material* findMaterial(const std::string& _name) const noexcept;

	const std::string& findMaterialName(const jl::Material& _material) const noexcept;

	void forEachMaterial(const std::function<void(const std::string&, jl::Material&)>& _callback);

private:
	MaterialsManager() = default;
	~MaterialsManager() = default;

	std::unordered_map<std::string, std::unique_ptr<jl::Material>> m_materials; // name => material
};
