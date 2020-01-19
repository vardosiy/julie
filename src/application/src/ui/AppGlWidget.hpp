#pragma once

#include "Sandbox.hpp"

#include <QOpenGLWidget>
#include <QTimer>

class AppGlWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	AppGlWidget(QWidget* _parent = nullptr);

protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* _event) override;
	void keyReleaseEvent(QKeyEvent* _event) override;

private slots:
	void update();

private:
	float getDeltaTime();

private:
	Sandbox m_sandbox;
	QTimer m_updateTimer;
};
