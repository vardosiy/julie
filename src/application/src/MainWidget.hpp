#pragma once

#include <QOpenGLWidget>
#include <QTimer>

class MainWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget * _parent = nullptr);

protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent * _event) override;
	void keyReleaseEvent(QKeyEvent * _event) override;

private slots:
	void update();

private:
	QTimer m_updateTimer;
};
