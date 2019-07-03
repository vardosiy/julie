#ifndef __NOTES_FOLDER_HPP__
#define __NOTES_FOLDER_HPP__

//-----------------------------------------------------------------------------

#include "NodesFwd.hpp"

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class NotesFolder : public HierarchyNode
{
public:
	NotesFolder() noexcept = default;
	NotesFolder(std::string_view _name) noexcept;

	std::string_view getName() const noexcept;
	void setName(std::string_view _name) noexcept;

	void addChildNode(HierarchyNodePtr _node) noexcept;
	int getChildNodesCount() const noexcept;

	void forEachChildNode(std::function<void(HierarchyNode &)> _callback);

	enums::NodeKind::Enum getKind() const noexcept override;

	void accept(Visitor & _visitor) override;

private:
	std::string m_name;
	std::vector<HierarchyNodePtr> m_childNodes;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __NOTES_FOLDER_HPP__
