#pragma once

#include "renderer/common/Types.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class VertexBufferLayout
{
public:
	enum class Type
	{

	};

	struct Item
	{

	};

public:
	void addItem(const Item & _item);

private:
	std::vector<Item> m_layoutItems;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
