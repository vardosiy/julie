#include "ui/MainWidget.hpp"

#include "renderer/Globals.hpp"

#include <iostream>
#include <QApplication>

//-----------------------------------------------------------------------------

int main(int _argc, char * _argv[])
{
	QApplication app(_argc, _argv);

	MainWidget widget;
	widget.show();

	return app.exec();
}

//-----------------------------------------------------------------------------
