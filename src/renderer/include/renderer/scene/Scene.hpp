#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/AmbientLightData.hpp"
#include "renderer/scene/FogData.hpp"

#include "utils/Singleton.hpp"

#include <glm/glm.hpp>

#include <functional>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Object;

class Scene : public utils::Singleton<Scene>
{
	friend class utils::Singleton<Scene>;

public:
	void draw(const Camera & _camera);
	void update(float _deltaTime);

	const FogData &				getFogData() const noexcept				{ return m_fogData; }
	const AmbientLightData &	getAmbientLightData() const noexcept	{ return m_ambientLightData; }

	void setFogData(const FogData & _data) noexcept;
	void setAmbientLightData(const AmbientLightData & _data) noexcept;

	void setPrerenderCommand(const std::function<void()> & _callback) noexcept;
	void setPostrenderCommand(const std::function<void()> & _callback) noexcept;

	void addObject(s32 _id, std::unique_ptr<Object> && _object);

	Object *		findObject(s32 _id) noexcept;
	const Object *	findObject(s32 _id) const noexcept;

	void forEachObject(const std::function<void(s32, Object &)> & _callback);
	void forEachObject(const std::function<void(s32, const Object &)> & _callback) const;

protected:
	Scene();
	~Scene();

private:
	std::unordered_map<s32, std::unique_ptr<Object>> m_objects;

	FogData m_fogData;
	AmbientLightData m_ambientLightData;

	std::function<void()> m_prerenderCallback;
	std::function<void()> m_postrenderCallback;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
