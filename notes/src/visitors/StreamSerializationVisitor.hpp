#ifndef __STREAM_SERIALIZATION_VISITOR_HPP__
#define __STREAM_SERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "Visitor.hpp"

//-----------------------------------------------------------------------------

class StreamSerializationVisitor : public Visitor
{
public:
	StreamSerializationVisitor(std::ostream & _stream) noexcept;

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	void serializeNodeKind(nodes::HierarchyNode & _node);

private:
	std::ostream & m_stream;
};

//-----------------------------------------------------------------------------

#endif // __STREAM_SERIALIZATION_VISITOR_HPP__
