#include "Pch.hpp"

#include <iostream>
#include <sstream>

//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

#include "nodes/NodesFactory.hpp"

#include "nodes/Note.hpp"
#include "nodes/NotesFolder.hpp"

#include "visitors/serialization/StreamSerializationVisitor.hpp"
#include "visitors/deserialization/StreamDeserializationVisitor.hpp"

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

	nodes::NodesFactory factory;
	
	auto note = factory.createNote("note");
	auto folder = factory.createNotesFolder("folder");
	folder->addChildNode(std::move(note));

	std::stringstream stream;

	visitors::StreamSerializationVisitor serializationVisitor(stream);
	folder->accept(serializationVisitor);

	visitors::StreamDeserializationVisitor deserializationVisitor(stream);
	auto result = deserializationVisitor.run();

	return 0;
}

//-----------------------------------------------------------------------------
