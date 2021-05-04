#pragma once

#include "CommonDefs.hpp"

#include "controllers/FreeflyCameraController.hpp"

#include "julie/ecs/RenderSystem.hpp"
#include "julie/ecs/TransformProcessSystem.hpp"

#include "julie/core/Types.hpp"
#include "julie/scene/Scene.hpp"
#include "julie/scene/Camera.hpp"

//-----------------------------------------------------------------------------

class GameCore
{
public:
	GameCore();
	~GameCore();

	jl::Scene* getScene() noexcept { return &m_scene; }
	jl::Camera* getCamera() noexcept { return &m_camera; }

	void init();
	void update(DeltaTime _dt);
	void render();

private:
	void initScene();
	void initDefaultMaterial();

	jl::Scene m_scene;
	jl::Camera m_camera;

	jl::ecs::RenderSystem m_renderSystem;
	jl::ecs::TransformProcessSystem m_transformProcessSystem;

	FreeflyCameraController m_cameraController;
};

//-----------------------------------------------------------------------------
