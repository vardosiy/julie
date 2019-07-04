#ifndef __STREAM_SERIALIZATION_VISITOR_HPP__
#define __STREAM_SERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "visitors/Visitor.hpp"
#include "save_restore_helpers/StreamWritingHelper.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

class StreamSerializationVisitor
	: public Visitor
	, private save_restore::StreamWritingHelper
{
public:
	StreamSerializationVisitor(std::ostream & _stream) noexcept;

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void serializeNodeKind(nodes::HierarchyNode & _node);
};

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------

#endif // __STREAM_SERIALIZATION_VISITOR_HPP__
