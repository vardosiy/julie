#include "ui/MainWindow.hpp"

#include <QApplication>

//-----------------------------------------------------------------------------

int main(int _argc, char* _argv[])
{
	QApplication app(_argc, _argv);

	MainWindow window;
	window.showMaximized();

	return app.exec();
}

//-----------------------------------------------------------------------------
