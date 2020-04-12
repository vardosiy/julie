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

	jl::Material& getMaterial(const std::string& _name) noexcept;
	const std::string& getMaterialName(const jl::Material& _material) const noexcept;

	void forEachMaterial(const std::function<void(const std::string&, jl::Material&)>& _callback);

private:
	MaterialsManager() = default;
	~MaterialsManager() = default;

	std::unordered_map<std::string, jl::Material> m_materials; // name => material
};
