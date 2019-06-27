#ifndef __NOTES_FOLDER_HPP__
#define __NOTES_FOLDER_HPP__

//-----------------------------------------------------------------------------

#include "HierarchyItem.hpp"

//-----------------------------------------------------------------------------

class NotesFolder : public HierarchyItem
{
public:
	NotesFolder();
	~NotesFolder();

	std::string_view getName() const noexcept;
	void setName(std::string_view _newName) noexcept;

	void addItem(std::unique_ptr<HierarchyItem> _item);

private:
	std::string m_name;
	std::vector<std::unique_ptr<HierarchyItem>> m_content;
};

//-----------------------------------------------------------------------------

#endif // __NOTES_FOLDER_HPP__
