#ifndef __NOTE_HPP__
#define __NOTE_HPP__

//-----------------------------------------------------------------------------

#include "HierarchyNode.hpp"

//-----------------------------------------------------------------------------

namespace nodes {

//-----------------------------------------------------------------------------

class Note : public HierarchyNode
{
public:
	Note() noexcept;
	Note(std::string_view _text) noexcept;

	std::string_view getText() const noexcept;
	void setText(std::string_view _text) noexcept;

	void accept(visitors::Visitor & _visitor) override;

private:
	std::string m_text;
};

//-----------------------------------------------------------------------------

} // namespace nodes

//-----------------------------------------------------------------------------

#endif // __NOTE_HPP__
