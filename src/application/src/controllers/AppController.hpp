#pragma once

#include <QOpenGLWidget>

class AppController
{
public:
	static void setGlWidget(QOpenGLWidget* _widget);
	static void makeContextCurrent();

private:
	static QOpenGLWidget* s_widget;
};
