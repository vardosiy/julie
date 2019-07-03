#include "Pch.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

//-----------------------------------------------------------------------------

int main(int _argc, char * _argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(_argc, _argv);
	QQmlApplicationEngine engine;

	const QUrl url(QStringLiteral("qrc:/ui/Main.qml"));
	engine.load(url);

	return app.exec();
}

//-----------------------------------------------------------------------------
