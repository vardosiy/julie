//#pragma once
//
//#include "renderer/scene/Camera.hpp"
//#include "renderer/scene/Scene.hpp"
//#include "renderer/Model.hpp"
//#include "renderer/Shader.hpp"
//#include "renderer/Texture.hpp"
//
//#include "data/Object.hpp"
//#include "data/Material.hpp"
//
//#include <vector>
//#include <memory>
//
//class Sandbox
//{
//public:
//	void init();
//	void update(float _dt);
//	void draw();
//
//	void onWindowResized(jl::u32 _w, jl::u32 _h);
//
//private:
//	void initResources();
//
//	jl::Scene m_scene;
//
//	std::unique_ptr<jl::Camera> m_camera;
//
//	std::vector<std::unique_ptr<data::Object>> m_objects;
//	std::vector<std::unique_ptr<data::Material>> m_materials;
//
//	std::vector<std::unique_ptr<jl::Shader>> m_shaders;
//	std::vector<std::unique_ptr<jl::Model>> m_models;
//	std::vector<std::unique_ptr<jl::Texture>> m_textures;
//	//std::vector<std::unique_ptr<jl::Material>> m_materials;
//};
