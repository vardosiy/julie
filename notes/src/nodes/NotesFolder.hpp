#ifndef __NOTES_FOLDER_HPP__
#define __NOTES_FOLDER_HPP__

//-----------------------------------------------------------------------------

#include "NodesFwd.hpp"

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

class NotesFolder : public HierarchyNode
{
public:
	NotesFolder(std::string_view _name);

	std::string_view getName() const noexcept;
	void setName(std::string_view _name) noexcept;

	void addNode(HierarchyNodePtr _node);
	int getNodesCount() const noexcept;
	const HierarchyNode & getNode(int _idx);

private:
	std::string m_name;
	std::vector<HierarchyNodePtr> m_childNodes;
};

//-----------------------------------------------------------------------------

#endif // __NOTES_FOLDER_HPP__
