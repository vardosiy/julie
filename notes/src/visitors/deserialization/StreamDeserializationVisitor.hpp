#ifndef __STREAM_DESERIALIZATION_VISITOR_HPP__
#define __STREAM_DESERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "visitors/Visitor.hpp"
#include "save_restore_helpers/StreamReadingHelper.hpp"

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

class StreamDeserializationVisitor
	: public Visitor
	, private save_restore::StreamReadingHelper
{
public:
	StreamDeserializationVisitor(std::istream & _stream) noexcept;

	nodes::HierarchyNodePtr run();

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	nodes::HierarchyNodePtr deserializeNode();
};

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------

#endif // __STREAM_DESERIALIZATION_VISITOR_HPP__
