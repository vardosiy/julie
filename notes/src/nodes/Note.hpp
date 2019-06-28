#ifndef __NOTE_HPP__
#define __NOTE_HPP__

//-----------------------------------------------------------------------------

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

class Note : public HierarchyNode
{
public:
	Note() noexcept = default;
	Note(std::string_view _text) noexcept;

	std::string_view getText() const noexcept;
	void setText(std::string_view _text) noexcept;

	NodeKind::Enum getKind() const noexcept override;

	void accept(Visitor & _visitor) override;

private:
	std::string m_text;
};

//-----------------------------------------------------------------------------

#endif // __NOTE_HPP__
