#pragma once

#include "core/nodes/NodesFwd.hpp"
#include "core/nodes/HierarchyNode.hpp"

#include <vector>
#include <functional>

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class NotesFolder : public HierarchyNode
{
public:
	NotesFolder() noexcept;
	explicit NotesFolder(std::string_view _name) noexcept;

	std::string_view getName() const noexcept;
	void setName(std::string_view _name) noexcept;

	void addChild(HierarchyNodePtr _node) noexcept;
	void removeChild(const HierarchyNode & _node) noexcept;
	int getChildrenCount() const noexcept;

	void forEachChildNode(std::function<void(HierarchyNode &)> _callback);
	void forEachChildNode(std::function<void(const HierarchyNode &)> _callback) const;

	void accept(visitors::Visitor & _visitor) override;

private:
	std::string m_name;
	std::vector<HierarchyNodePtr> m_childNodes;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
