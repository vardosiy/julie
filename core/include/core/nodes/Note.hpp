#pragma once

#include "core/nodes/HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class Note : public HierarchyNode
{
public:
	Note() noexcept;
	explicit Note(std::string_view _text) noexcept;

	std::string_view getText() const noexcept;
	void setText(std::string_view _text) noexcept;

	void accept(visitors::Visitor & _visitor) override;

private:
	std::string m_text;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
