#pragma once

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"
#include "julie/Vertex.hpp"

#include "utils/Noncopyable.hpp"
#include "utils/FastPimpl.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;
class MeshImpl;

class Mesh : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	Mesh(const std::vector<Vertex>& _vertices, const std::vector<u32>& _indices) noexcept;
	~Mesh() noexcept;

	Mesh(Mesh&& _rhs) noexcept;
	Mesh& operator=(Mesh&& _rhs) noexcept;

//-----------------------------------------------------------------------------
	void bind() const;

	Material* getMaterial() noexcept;
	const Material* getMaterial() const noexcept;
	void setMaterial(Material* _material) noexcept;

	u64 getIndicesCount() const noexcept;
	const aabbf& getBoundingBox() const noexcept;

//-----------------------------------------------------------------------------
private:
	static constexpr size_t k_implSize{ 12 };
	static constexpr size_t k_implAlign{ 8 };
	utils::FastPimpl<MeshImpl, k_implSize, k_implAlign> m_impl;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
