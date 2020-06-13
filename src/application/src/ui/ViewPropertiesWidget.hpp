#pragma once

#include <QWidget>

#include <memory>

namespace Ui {
class ViewPropertiesWidget;
}

class AppGlWidget;
class FreeflyCameraController;

class ViewPropertiesWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ViewPropertiesWidget(QWidget* parent = nullptr);

	void update(float _dt) noexcept;

	void setGlWidget(AppGlWidget* _glWidget) noexcept;
	void setCameraController(FreeflyCameraController* _camContoller) noexcept;

private slots:
	void onCamMoveSpeedChanged(int _value);
	void onCamRotateSpeedChanged(int _value);
	void onCamMoveSpeedChanged(float _value);
	void onCamRotateSpeedChanged(float _value);

	void onFillPolygonsValueChanged(int _state);

private:
	std::unique_ptr<Ui::ViewPropertiesWidget> m_ui;

	AppGlWidget* m_glWidget;
	FreeflyCameraController* m_camController;

	bool m_editingValue;
};
