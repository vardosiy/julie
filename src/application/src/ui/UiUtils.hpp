#include <QString>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <fmt/format.h>

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
