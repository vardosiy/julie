#include "Pch.hpp"

#include "Note.hpp"

//-----------------------------------------------------------------------------

Note::Note(std::string_view _text) noexcept
	: m_text(_text)
	, m_tag(NoteTag::NonTaged)
{
	// TODO validation
}

//-----------------------------------------------------------------------------

Note::~Note()
{
}

//-----------------------------------------------------------------------------

std::string_view Note::getText() const noexcept
{
	return m_text;
}

//-----------------------------------------------------------------------------

NoteTag Note::getTag() const noexcept
{
	return m_tag;
}

//-----------------------------------------------------------------------------

void Note::setText(std::string_view _text) noexcept
{
	m_text = _text;
}

//-----------------------------------------------------------------------------

void Note::setTag(NoteTag _tag) noexcept
{
	m_tag = _tag;
}

//-----------------------------------------------------------------------------
