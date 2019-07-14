#ifndef __STREAM_DESERIALIZATION_VISITOR_HPP__
#define __STREAM_DESERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "visitors/Visitor.hpp"
#include "utils/StreamReader.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

class StreamDeserializationVisitor
	: public Visitor
	, private utils::save_restore::StreamReader
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

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------

#endif // __STREAM_DESERIALIZATION_VISITOR_HPP__
