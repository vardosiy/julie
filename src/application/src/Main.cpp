#include <sstream>
#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "core/Model.hpp"

#include "core/nodes/NodesFactory.hpp"
#include "core/nodes/Note.hpp"
#include "core/nodes/NotesFolder.hpp"

#include "core/visitors/save_restore/StreamSaveVisitor.hpp"
#include "core/visitors/save_restore/StreamRestoreVisitor.hpp"

#include "utils/Assert.hpp"

//-----------------------------------------------------------------------------

nodes::NotesFolderPtr createFolderWithFewChilds(std::string_view _name)
{
	auto folder = nodes::NodesFactory::createNotesFolder(_name);

	folder->addChild(nodes::NodesFactory::createNote("note1"));
	folder->addChild(nodes::NodesFactory::createNote("note2"));
	folder->addChild(nodes::NodesFactory::createNote("note3"));
	folder->addChild(nodes::NodesFactory::createNote("note4"));

	return folder;
}

nodes::NotesFolderPtr createBaseStructure()
{
	auto root = nodes::NodesFactory::createNotesFolder("root");

	root->addChild(nodes::NodesFactory::createNote("note1"));
	root->addChild(createFolderWithFewChilds("folder1"));
	root->addChild(nodes::NodesFactory::createNote("note2"));
	root->addChild(createFolderWithFewChilds("folder2"));
	root->addChild(nodes::NodesFactory::createNote("note3"));
	root->addChild(createFolderWithFewChilds("folder3"));
	root->addChild(nodes::NodesFactory::createNote("note4"));
	root->addChild(createFolderWithFewChilds("folder4"));

	return root;
}

//-----------------------------------------------------------------------------

void test(nodes::NotesFolderPtr & _folder)
{
	_folder->forEachChildNode(
		[&_folder](const nodes::HierarchyNode & _node)
		{
			if (_node.getKind() == enums::NodeKind::Note)
				_folder->removeChild(_node);
		}
	);

	_folder->forEachChildNode(
		[](const nodes::HierarchyNode & _node)
		{
			if (_node.getKind() == enums::NodeKind::Note)
				ASSERT_FALSE("Wrong erase logic");
		}
	);
}

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

	auto folder = createBaseStructure();

	std::stringstream stream;

	visitors::save_restore::StreamSaveVisitor serializationVisitor(stream);
	folder->accept(serializationVisitor);

	visitors::save_restore::StreamRestoreVisitor deserializationVisitor(stream);
	nodes::NotesFolder restoredRoot;
	restoredRoot.accept(deserializationVisitor);

	ASSERT(folder->getChildrenCount() == 8, "");
	test(folder);
	ASSERT(folder->getChildrenCount() == 4, "");

	auto & test = Model::getInstance();

	return 0;
}

//-----------------------------------------------------------------------------
