#include "ui/MainWidget.hpp"

#include <QApplication>

//-----------------------------------------------------------------------------

int main(int _argc, char* _argv[])
{
	QApplication app(_argc, _argv);

	MainWidget widget;
	widget.showMaximized();

	return app.exec();
}

//-----------------------------------------------------------------------------
