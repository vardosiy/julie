#include "Pch.hpp"

#include "Note.hpp"

#include "visitors/Visitor.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

Note::Note(std::string_view _text) noexcept
	: m_text{ _text }
{
}

//-----------------------------------------------------------------------------

std::string_view Note::getText() const noexcept
{
	return m_text;
}

//-----------------------------------------------------------------------------

void Note::setText(std::string_view _text) noexcept
{
	m_text = _text;
}

//-----------------------------------------------------------------------------

enums::NodeKind::Enum Note::getKind() const noexcept
{
	return enums::NodeKind::Note;
}

//-----------------------------------------------------------------------------

void Note::accept(Visitor & _visitor)
{
	_visitor(*this);
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
