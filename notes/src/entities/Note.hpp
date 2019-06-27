#ifndef __NOTE_HPP__
#define __NOTE_HPP__

//-----------------------------------------------------------------------------

#include "HierarchyItem.hpp"
#include "enums/NoteTag.hpp"

//-----------------------------------------------------------------------------

class Note : public HierarchyItem
{
public:
	Note(std::string_view _text) noexcept;

	std::string_view getText() const noexcept;
	NoteTag getTag() const noexcept;

	void setText(std::string_view _text) noexcept;
	void setTag(NoteTag _tag) noexcept;

private:
	std::string m_text;

	NoteTag m_tag;
};

//-----------------------------------------------------------------------------

#endif // __NOTE_HPP__
