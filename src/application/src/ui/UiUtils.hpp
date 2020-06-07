#include <QString>
#include <QVector3D>
#include <QVector4D>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <fmt/format.h>

//-----------------------------------------------------------------------------

inline glm::vec3 toGlmVec(const QVector3D& _vec)	{ return glm::vec3(_vec.x(), _vec.y(), _vec.z()); }
inline glm::vec4 toGlmVec(const QVector4D& _vec)	{ return glm::vec4(_vec.x(), _vec.y(), _vec.z(), _vec.w()); }

inline QVector3D toQtVec(const glm::vec3& _vec)		{ return QVector3D(_vec.x, _vec.y, _vec.z); }
inline QVector4D toQtVec(const glm::vec4& _vec)		{ return QVector4D(_vec.x, _vec.y, _vec.z, _vec.w); }

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

inline QString vecToString(const QVector3D& _vec)		{ return vecToString(toGlmVec(_vec)); }
inline QString vecToString(const QVector4D& _vec)		{ return vecToString(toGlmVec(_vec)); }

//-----------------------------------------------------------------------------
