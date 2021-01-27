#pragma once

#include "julie/managers/ResourceManager.hpp"

#include <QString>
#include <fmt/format.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

//-----------------------------------------------------------------------------

constexpr double k_floatUiMin	= -1000.0f;
constexpr double k_floatUiMax	=  1000.0f;
constexpr double k_floatUiStep	=  0.1f;
constexpr int k_floatDecimals	=  4;

//-----------------------------------------------------------------------------

inline QString vecToString(const glm::vec3& _vec)
{
	const std::string str = fmt::format("[{:.4f} {:.4f} {:.4f}]", _vec.x, _vec.y, _vec.z);
	return QString::fromStdString(str);
}

inline QString vecToString(const glm::vec4& _vec)
{
	const std::string str = fmt::format("[{:.4f} {:.4f} {:.4f} {:.4f}]", _vec.x, _vec.y, _vec.z, _vec.w);
	return QString::fromStdString(str);
}

//-----------------------------------------------------------------------------

template<typename T>
inline QString findSourceFile(const T* _resource)
{
	return _resource ? jl::ResourceManager::getInstance().findSourceFile(*_resource).c_str() : "";
}

//-----------------------------------------------------------------------------

struct ScopedFlagSwitcher
{
	ScopedFlagSwitcher(bool& _val)
		: m_value(_val)
	{
		m_value = !m_value;
	}

	~ScopedFlagSwitcher()
	{
		m_value = !m_value;
	}

	bool& m_value;
};

//-----------------------------------------------------------------------------
