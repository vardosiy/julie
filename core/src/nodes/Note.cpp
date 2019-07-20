#include "Pch.hpp"

#include "core/nodes/Note.hpp"

#include "core/visitors/Visitor.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

Note::Note() noexcept
	: HierarchyNode{ enums::NodeKind::Note }
{
}

//-----------------------------------------------------------------------------

Note::Note(std::string_view _text) noexcept
	: Note()
{
	m_text = _text;
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

void Note::accept(visitors::Visitor & _visitor)
{
	_visitor(*this);
}

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------
