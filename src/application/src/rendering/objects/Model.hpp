#pragma once

#include "rendering/common/Vertex.hpp"

#include <glad/glad.h>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <vector>
#include <memory>

class Model : boost::noncopyable
{
public:
	static std::unique_ptr<Model> create(std::string_view _filePath);
	static std::unique_ptr<Model> createRect();

public:
	~Model();

	Model(Model && _rhs) noexcept;
	Model & operator =(Model && _rhs) noexcept;

	void bind() const;

	int getVerteciesCount() const noexcept	{ return m_verticesCount; }
	int getIndeciesCount() const noexcept	{ return m_indicesCount; }

private:
	Model(const std::vector<Vertex> & _vertices, const std::vector<uint16_t> & _indices);

private:
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;

	int m_verticesCount;
	int m_indicesCount;
};
