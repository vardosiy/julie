#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/AmbientLightData.hpp"

#include "utils/Singleton.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Shader;
class Object;

class Scene : public utils::Singleton<Scene>
{
	friend class utils::Singleton<Scene>;

public:
	void draw(const Camera& _camera);
	void update(float _dt);

	const FogData* getFogData() const noexcept;
	const AmbientLightData* getAmbientLightData() const noexcept;

	void setFogData(const FogData& _data) noexcept;
	void setAmbientLightData(const AmbientLightData& _data) noexcept;

	void setPrerenderCommand(const std::function<void()>& _callback) noexcept;
	void setPostrenderCommand(const std::function<void()>& _callback) noexcept;

	void addObject(s32 _id, std::unique_ptr<Object>&& _object);

	Object* findObject(s32 _id) noexcept;
	const Object* findObject(s32 _id) const noexcept;

	void forEachObject(const std::function<void(s32, Object&)>& _callback);
	void forEachObject(const std::function<void(s32, const Object&)>& _callback) const;

private:
	Scene();
	~Scene();

	void drawObject(const Camera& _camera, const Object& _object) const noexcept;

private:
	std::unordered_map<s32, std::unique_ptr<Object>> m_objects;

	boost::optional<FogData> m_fogData;
	boost::optional<AmbientLightData> m_ambientLightData;

	std::function<void()> m_prerenderCallback;
	std::function<void()> m_postrenderCallback;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
