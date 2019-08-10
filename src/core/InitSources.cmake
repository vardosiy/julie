set (SOURCES
	include/core/enums/NodeKind.hpp
	include/core/enums/NodeTag.hpp
	include/core/nodes/HierarchyNode.hpp
	include/core/nodes/NodesFactory.hpp
	include/core/nodes/NodesFwd.hpp
	include/core/nodes/Note.hpp
	include/core/nodes/NotesFolder.hpp
	include/core/visitors/save_restore/StreamRestoreVisitor.hpp
	include/core/visitors/save_restore/StreamSaveVisitor.hpp
	include/core/visitors/Visitor.hpp
	src/nodes/HierarchyNode.cpp
	src/nodes/NodesFactory.cpp
	src/nodes/Note.cpp
	src/nodes/NotesFolder.cpp
	src/visitors/save_restore/StreamRestoreVisitor.cpp
	src/visitors/save_restore/StreamSaveVisitor.cpp
)