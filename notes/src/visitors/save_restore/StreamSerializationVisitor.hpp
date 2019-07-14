#ifndef __STREAM_SERIALIZATION_VISITOR_HPP__
#define __STREAM_SERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "visitors/Visitor.hpp"
#include "utils/StreamWriter.hpp"

//-----------------------------------------------------------------------------

namespace visitors::save_restore {

//-----------------------------------------------------------------------------

class StreamSerializationVisitor
	: public Visitor
	, private utils::save_restore::StreamWriter
{
public:
	StreamSerializationVisitor(std::ostream & _stream) noexcept;

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void serializeCommon(nodes::HierarchyNode & _node);
};

//-----------------------------------------------------------------------------

} // namespace visitors::save_restore

//-----------------------------------------------------------------------------

#endif // __STREAM_SERIALIZATION_VISITOR_HPP__
