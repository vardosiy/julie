#include "MainWidget.hpp"

#include "renderer/common/Globals.hpp"

#include <iostream>
#include <QApplication>

//-----------------------------------------------------------------------------

int main(int _argc, char * _argv[])
{
	QApplication app(_argc, _argv);

	MainWidget widget;
	widget.setFixedSize(jl::Globals::s_screenWidth, jl::Globals::s_screenHeight);
	widget.show();

	return app.exec();
}

//-----------------------------------------------------------------------------
