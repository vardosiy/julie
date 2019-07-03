#ifndef __STREAM_DESERIALIZATION_VISITOR_HPP__
#define __STREAM_DESERIALIZATION_VISITOR_HPP__

//-----------------------------------------------------------------------------

#include "Visitor.hpp"

//-----------------------------------------------------------------------------

class StreamDeserializationVisitor : public Visitor
{
public:
	StreamDeserializationVisitor(std::istream & _stream) noexcept;

	// return root folder
	nodes::NotesFolderPtr run();

	void operator() (nodes::Note & _note) override;
	void operator() (nodes::NotesFolder & _notesFolder) override;

private:
	nodes::HierarchyNodePtr deserializeNode();

	std::istream & m_stream;
};

//-----------------------------------------------------------------------------

#endif // __STREAM_DESERIALIZATION_VISITOR_HPP__
