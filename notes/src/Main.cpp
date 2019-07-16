#include <sstream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "core/nodes/NodesFactory.hpp"
#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

#include "core/visitors/save_restore/StreamSerializationVisitor.hpp"
#include "core/visitors/save_restore/StreamDeserializationVisitor.hpp"

#include "utils/Assert.hpp"

//-----------------------------------------------------------------------------

int main(int _argc, char * _argv[])
{
	//QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	//
	//QGuiApplication app(_argc, _argv);
	//QQmlApplicationEngine engine;
	//
	//const QUrl url(QStringLiteral("qrc:/ui/Main.qml"));
	//engine.load(url);
	//
	//return app.exec();

	auto note = nodes::NodesFactory::createNote("note");
	auto folder = nodes::NodesFactory::createNotesFolder("folder");
	folder->addChildNode(std::move(note));
	
	std::stringstream stream;
	
	visitors::save_restore::StreamSerializationVisitor serializationVisitor(stream);
	folder->accept(serializationVisitor);
	
	visitors::save_restore::StreamDeserializationVisitor deserializationVisitor(stream);
	auto result = deserializationVisitor.run();
	
	ASSERT(folder->getChildNodesCount() == 1, "");
	std::vector<const nodes::HierarchyNode *> test;
	folder->forEachChildNode([&test](const nodes::HierarchyNode & _node) { test.push_back(&_node); });
	folder->removeChildNode(*test[0]);
	ASSERT(folder->getChildNodesCount() == 0, "");

	return 0;
}

//-----------------------------------------------------------------------------
