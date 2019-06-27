#include "Pch.hpp"

#include "Notes.hpp"

#include <QtWidgets/QApplication>

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	NotesWidget widget;
	widget.show();

	return app.exec();
}

//-----------------------------------------------------------------------------
