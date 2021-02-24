#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>

namespace jl {
class Model;
}

struct TagComponent
{
	TagComponent(std::string _tag) noexcept
		: tag(std::move(_tag))
	{
	}

	TagComponent() noexcept = default;

	std::string tag;
};

struct TransformComponent
{
	TransformComponent(const glm::vec3& _pos, const glm::vec3& _scale, const glm::vec3& _rotation) noexcept
		: pos(_pos)
		, scale(_scale)
		, rotation(_rotation)
	{
	}

	TransformComponent() noexcept = default;

	glm::vec3 pos{ 0.0f };
	glm::vec3 scale{ 1.0f };
	glm::vec3 rotation{ 0.0f };
};

struct WorldMatComponent
{
	WorldMatComponent() noexcept = default;

	glm::mat4 worldMat{ 1.0f };
};

struct LightSourceComponent
{
	LightSourceComponent(const glm::vec3& _direction, const glm::vec3& _color) noexcept
		: direction(_direction)
		, color(_color)
	{
	}

	LightSourceComponent() noexcept = default;

	glm::vec3 direction{ 0.0f };
	glm::vec3 color{ 1.0f };
};

struct RenderComponent
{
};

struct ModelComponent
{
	ModelComponent(jl::Model* _model) noexcept
		: model(_model)
	{
	}

	ModelComponent() noexcept = default;

	jl::Model* model{ nullptr };
};
