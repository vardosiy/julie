#ifndef __STREAM_SERIALIZATION_VISITOR_HPP__
#define __STREAM_SERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "Visitor.hpp"

//-----------------------------------------------------------------------------

class StreamSerializationVisitor : public Visitor
{
public:
	StreamSerializationVisitor(std::ostream & _stream) noexcept;

	void visit(Note & _note) override;
	void visit(NotesFolder & _notesFolder) override;

private:
	void serializeNodeKind(HierarchyNode & _node);

	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

#endif // __STREAM_SERIALIZATION_VISITOR_HPP__
