#include "AppController.hpp"

//-----------------------------------------------------------------------------

QOpenGLWidget* AppController::s_widget = nullptr;

//-----------------------------------------------------------------------------

void AppController::setGlWidget(QOpenGLWidget* _widget)
{
	s_widget = _widget;
}

//-----------------------------------------------------------------------------

void AppController::makeContextCurrent()
{
	if (s_widget)
	{
		s_widget->makeCurrent();
	}
}

//-----------------------------------------------------------------------------
