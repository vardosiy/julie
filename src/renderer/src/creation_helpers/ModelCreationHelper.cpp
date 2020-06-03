#include "creation_helpers/ModelCreationHelper.hpp"

#include "renderer/Model.hpp"

#include "utils/Utils.hpp"

#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::vector<std::unique_ptr<Model>> g_models;

std::unique_ptr<Model> processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<u16> indices;

	for (u32 i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.pos = glm::vec3{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		vertex.norm = glm::vec3{ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		vertex.uv = mesh->mTextureCoords[0] ? glm::vec2{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y } : glm::vec2{ 0.0f };

		vertices.push_back(vertex);
	}

	for (u32 i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (u32 j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return std::make_unique<Model>(vertices, indices);
}

void processNode(aiNode* node, const aiScene* scene)
{
	for (u32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		g_models.push_back(processMesh(mesh, scene));
	}

	for (u32 i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

void loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return;
	}

	processNode(scene->mRootNode, scene);
}

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

	}

	return nullptr;
}

//-----------------------------------------------------------------------------

std::vector<std::unique_ptr<Model>> ModelCreationHelper::load(std::string_view _filePath)
{
	loadModel(_filePath.data());

	std::vector<std::unique_ptr<Model>> result;
	std::swap(result, g_models);
	return result;
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
			&vertex.pos.x, &vertex.pos.y, &vertex.pos.z,
			&vertex.norm.x, &vertex.norm.y, &vertex.norm.z,
			&vertex.bitangent.x, &vertex.bitangent.y, &vertex.bitangent.z,
			&vertex.tangent.x, &vertex.tangent.y, &vertex.tangent.z,
			&vertex.uv.x, &vertex.uv.y
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

} // namespace jl

//-----------------------------------------------------------------------------
