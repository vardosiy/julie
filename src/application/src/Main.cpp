#include "MainWidget.hpp"

#include <QApplication>

//-----------------------------------------------------------------------------

int main(int _argc, char * _argv[])
{
	QApplication app(_argc, _argv);

	MainWidget widget;
	widget.setFixedSize(1600, 900);
	widget.show();

	return app.exec();
}

//-----------------------------------------------------------------------------
