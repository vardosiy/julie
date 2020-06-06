#include "creation_helpers/ModelCreationHelper.hpp"

#include "renderer/Model.hpp"
#include "renderer/Mesh.hpp"

#include "utils/Utils.hpp"

#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadFromFile(std::string_view _filePath)
{
	std::filesystem::path path(_filePath);

	if (path.extension() == ".nfg")
	{
		return loadNfg(_filePath);
	}
	else if (path.extension() == ".obj")
	{
		return loadObj(_filePath);
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadNfg(std::string_view _filePath)
{
	FILE* pFile = fopen(_filePath.data(), "r");
	if (!pFile)
	{
		return nullptr;
	}

	int verticesCount = 0;
	fscanf_s(pFile, "%*s %d", &verticesCount);
	ASSERTM(verticesCount > 0, "Vercices count has invalid value in file {}", _filePath);

	std::vector<Vertex> vertices(verticesCount);
	for (Vertex& vertex : vertices)
	{
		fscanf_s(
			pFile, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&vertex.pos.x,			&vertex.pos.y,			&vertex.pos.z,
			&vertex.norm.x,			&vertex.norm.y,			&vertex.norm.z,
			&vertex.bitangent.x,	&vertex.bitangent.y,	&vertex.bitangent.z,
			&vertex.tangent.x,		&vertex.tangent.y,		&vertex.tangent.z,
			&vertex.uv.x,			&vertex.uv.y
		);
	}

	s32 indicesCount = 0;
	fscanf_s(pFile, "%*s %d", &indicesCount);
	ASSERTM(indicesCount > 0, "Vercices count has invalid value in file {}", _filePath);

	std::vector<u16> indices(indicesCount);
	for (s32 i = 0; i < indicesCount; i += 3)
	{
		fscanf_s(
			pFile, " %*d. %hd, %hd, %hd",
			&indices[i], &indices[i + 1], &indices[i + 2]
		);
	}

	fclose(pFile);

	return std::make_unique<Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadObj(std::string_view _filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_filePath.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode)
	{
		std::vector<Mesh> meshes;
		processNode(scene->mRootNode, scene, meshes);
		return std::make_unique<Model>(std::move(meshes));
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

void ModelCreationHelper::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& _meshes)
{
	for (u32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.emplace_back(processMesh(mesh, scene));
	}

	for (u32 i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, _meshes);
	}
}

//-----------------------------------------------------------------------------

Mesh ModelCreationHelper::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices(mesh->mNumVertices);
	std::vector<u16> indices;

	for (u32 i = 0; i < mesh->mNumVertices; ++i)
	{
		vertices[i].pos = glm::vec3{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		vertices[i].norm = glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

		vertices[i].uv = glm::vec2{ 0.0f };
		if (mesh->mTextureCoords[0])
		{
			vertices[i].uv = glm::vec2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
	}

	for (u32 i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (u32 j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(vertices, indices);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
