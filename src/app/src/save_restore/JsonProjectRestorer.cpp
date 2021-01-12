//#include "save_restore/JsonProjectRestorer.hpp"
//#include "save_restore/JsonStrings.hpp"
//
//#include "julie/managers/ResourceManager.hpp"
//#include "julie/managers/MaterialsManager.hpp"
//
//#include "julie/scene/Scene.hpp"
//#include "julie/scene/Object.hpp"
//
//#include "julie/Mesh.hpp"
//#include "julie/Model.hpp"
//#include "julie/Material.hpp"
//#include "julie/UniformType.hpp"
//
//#include "julie/scene/Scene.hpp"
//#include "julie/scene/Object.hpp"
//#include "julie/scene/lights/LightsHolder.hpp"
//
//#include "utils/Assert.hpp"
//
////-----------------------------------------------------------------------------
//
//namespace details {
//
////-----------------------------------------------------------------------------
//
//inline glm::vec2 jsonToVec2(const Json::Value& _val) noexcept
//{
//	if (_val.isArray() && _val.size() >= 2)
//	{
//		return glm::vec2(_val[0].asFloat(), _val[1].asFloat());
//	}
//	return glm::vec2(0.0f);
//}
//
//inline glm::vec3 jsonToVec3(const Json::Value& _val) noexcept
//{
//	if (_val.isArray() && _val.size() >= 3)
//	{
//		return glm::vec3(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat());
//	}
//	return glm::vec3(0.0f);
//}
//
//inline glm::vec4 jsonToVec4(const Json::Value& _val) noexcept
//{
//	if (_val.isArray() && _val.size() >= 4)
//	{
//		return glm::vec4(_val[0].asFloat(), _val[1].asFloat(), _val[2].asFloat(), _val[3].asFloat());
//	}
//	return glm::vec4(0.0f);
//}
//
////-----------------------------------------------------------------------------
//
//} // namespace details
//
////-----------------------------------------------------------------------------
//
//JsonProjectRestorer::JsonProjectRestorer(std::istream& _stream)
//{
//	Json::Value root;
//	_stream >> root;
//
//	restoreMaterials(root[k_materials]);
//
//	m_scene = restoreScene(root[k_scene]);
//}
//
////-----------------------------------------------------------------------------
//
//std::optional<jl::Scene> JsonProjectRestorer::extractScene()
//{
//	return std::move(m_scene);
//}
//
////-----------------------------------------------------------------------------
//
//void JsonProjectRestorer::restoreMaterials(const Json::Value& _json)
//{
//	for (const Json::Value& value : _json)
//	{
//		const std::string name = value[k_name].asString();
//		jl::Material& material = MaterialsManager::getInstance().createMaterial(name);
//
//		{
//			const std::string shaderPath = value[k_shader].asString();
//			jl::Shader* shader = ResourceManager::getInstance().loadShader(shaderPath);
//			ASSERT(shader);
//
//			material.setShader(shader);
//		}
//
//		restoreMaterialProperties(value[k_properties], material);
//	}
//}
//
////-----------------------------------------------------------------------------
//
//void JsonProjectRestorer::restoreMaterialProperties(const Json::Value& _json, jl::Material& _material)
//{
//	for (const Json::Value& value : _json)
//	{
//		const std::string name = value[k_name].asString();
//		const std::string type = value[k_type].asString();
//
//		const Json::Value& propertyValue = value[k_value];
//		switch (utils::fromString<jl::UniformType>(type))
//		{
//		case jl::UniformType::Int:
//			_material.setProperty(name, propertyValue.asInt());
//			break;
//
//		case jl::UniformType::Float:
//			_material.setProperty(name, propertyValue.asFloat());
//			break;
//
//		case jl::UniformType::Vec2:
//			_material.setProperty(name, details::jsonToVec2(propertyValue));
//			break;
//
//		case jl::UniformType::Vec3:
//			_material.setProperty(name, details::jsonToVec3(propertyValue));
//			break;
//
//		case jl::UniformType::Vec4:
//			_material.setProperty(name, details::jsonToVec4(propertyValue));
//			break;
//
//		case jl::UniformType::Texture2D:
//			{
//				const std::string path = propertyValue.asString();
//				if (!path.empty())
//				{
//					jl::Texture* texture = ResourceManager::getInstance().loadTexture(path);
//					ASSERT(texture);
//					_material.setProperty(name, texture);
//				}
//			}
//			break;
//
//		case jl::UniformType::CubeTexture:
//			{
//				const std::string path = propertyValue.asString();
//				if (!path.empty())
//				{
//					jl::CubeTexture* texture = ResourceManager::getInstance().loadCubeTexture(path);
//					ASSERT(texture);
//					_material.setProperty(name, texture);
//				}
//			}
//			break;
//
//		default:
//			ASSERT(0);
//		}
//	}
//}
//
////-----------------------------------------------------------------------------
//
//jl::Scene JsonProjectRestorer::restoreScene(const Json::Value& _json)
//{
//	jl::Scene scene;
//
//	for (const Json::Value& objectJson : _json[k_objects])
//	{
//		std::unique_ptr<jl::Object> object = restoreObject(objectJson);
//		scene.addObject(std::move(object));
//	}
//
//	restoreLights(_json[k_lights], scene.getLightsHolder());
//
//	return scene;
//}
//
////-----------------------------------------------------------------------------
//
//jl::Scene::ObjectPtr JsonProjectRestorer::restoreObject(const Json::Value& _json)
//{
//	auto object = std::make_unique<jl::Object>();
//
//	const std::string objectName = _json[k_name].asString();
//	object->setName(objectName);
//
//	const Json::Value& modelJson = _json[k_model];
//	if (!_json.isNull())
//	{
//		jl::Model* model = restoreModel(modelJson);
//		object->setModel(model);
//	}
//
//	object->setPosition(details::jsonToVec3(_json[k_position]));
//	object->setRotation(details::jsonToVec3(_json[k_rotation]));
//	object->setScale(details::jsonToVec3(_json[k_scale]));
//
//	return object;
//}
//
////-----------------------------------------------------------------------------
//
//jl::Model* JsonProjectRestorer::restoreModel(const Json::Value& _json)
//{
//	const std::string modelPath = _json[k_path].asString();
//	if (modelPath.empty())
//	{
//		return nullptr;
//	}
//
//	jl::Model* model = ResourceManager::getInstance().loadModel(modelPath, false /* _loadMaterials */);
//	ASSERT(model);
//	if (model)
//	{
//		Json::Value::ArrayIndex materialsToRead = 0;
//
//		const Json::Value& meshMaterials = _json[k_meshMaterials];
//		if (meshMaterials.isArray())
//		{
//			const size_t meshesCount = model->getMeshesCount();
//			materialsToRead = std::min(meshMaterials.size(), static_cast<Json::Value::ArrayIndex>(meshesCount));
//		}
//
//		for (Json::Value::ArrayIndex i = 0; i < materialsToRead; ++i)
//		{
//			const std::string materialName = meshMaterials[i].asString();
//			if (!materialName.empty())
//			{
//				jl::Material* material = MaterialsManager::getInstance().findMaterial(materialName);
//				ASSERT(material);
//
//				jl::Mesh& mesh = model->getMesh(i);
//				mesh.setMaterial(material);
//			}
//		}
//	}
//
//	return model;
//}
//
////-----------------------------------------------------------------------------
//
//void JsonProjectRestorer::restoreLights(const Json::Value& _json, jl::LightsHolder& _lightsHolder)
//{
//	for (const Json::Value& light : _json[k_pointLights])
//	{
//		jl::PointLightData lightData{ details::jsonToVec3(light[k_color]), details::jsonToVec3(light[k_position]) };
//		_lightsHolder.addPointLight(lightData);
//	}
//
//	for (const Json::Value& light : _json[k_directionalLights])
//	{
//		jl::DirectionalLightData lightData{ details::jsonToVec3(light[k_color]), details::jsonToVec3(light[k_direction]) };
//		_lightsHolder.addDirectionalLight(lightData);
//	}
//
//	const Json::Value& ambientlight = _json[k_ambientLight];
//
//	jl::AmbientLightData lightData{ details::jsonToVec3(ambientlight[k_color]), ambientlight[k_weight].asFloat() };
//	_lightsHolder.setAmbientLight(lightData);
//}
//
////-----------------------------------------------------------------------------
