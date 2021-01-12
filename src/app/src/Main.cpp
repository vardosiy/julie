#include "ui/MainWindow.hpp"

#include <QApplication>

#include "julie/ecs/Components.hpp"
#include "julie/ecs/ComponentsMgr.hpp"
#include "julie/ecs/EntitiesMgr.hpp"
#include "julie/ecs/Entity.hpp"

//-----------------------------------------------------------------------------

void test()
{
	jl::ecs::ComponentsMgr components;
	jl::ecs::EntitiesMgr enitites(components);
	jl::ecs::Entity& id = enitites.create("test");
}

int main(int _argc, char* _argv[])
{
	QApplication app(_argc, _argv);

	MainWindow window;
	window.showMaximized();

	return app.exec();
}

//-----------------------------------------------------------------------------
