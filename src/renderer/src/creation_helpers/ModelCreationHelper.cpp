#include "creation_helpers/ModelCreationHelper.hpp"

#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/MaterialsManager.hpp"

#include "renderer/Mesh.hpp"
#include "renderer/Model.hpp"
#include "renderer/Material.hpp"

#include "utils/Utils.hpp"

#include <filesystem>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadFromFile(std::string_view _filePath, bool _loadMaterials)
{
	std::filesystem::path path(_filePath);

	if (path.extension() == ".nfg")
	{
		return loadNfg(_filePath);
	}
	else if (path.extension() == ".obj")
	{
		return loadAssimp(_filePath, _loadMaterials);
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

	auto model = std::make_unique<Model>(vertices, indices);
	model->getMesh(0).setMaterial(&MaterialsManager::getInstance().getDefaultMaterial());
	return model;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadAssimp(std::string_view _filePath, bool _loadMaterials)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_filePath.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode)
	{
		ModelCreationHelper helper(_filePath, _loadMaterials);
		helper.processNode(scene->mRootNode, scene);
		return std::make_unique<Model>(std::move(helper.m_meshes));
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

ModelCreationHelper::ModelCreationHelper(std::string_view _filePath, bool _loadMaterials)
	: m_filePath(_filePath)
	, m_loadMaterials(_loadMaterials)
{
}

//-----------------------------------------------------------------------------

ModelCreationHelper::~ModelCreationHelper() = default;

//-----------------------------------------------------------------------------

void ModelCreationHelper::processNode(aiNode* _node, const aiScene* _scene)
{
	for (u32 i = 0; i < _node->mNumMeshes; i++)
	{
		aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
		m_meshes.emplace_back(processMesh(mesh, _scene));
	}

	for (u32 i = 0; i < _node->mNumChildren; i++)
	{
		processNode(_node->mChildren[i], _scene);
	}
}

//-----------------------------------------------------------------------------

Mesh ModelCreationHelper::processMesh(aiMesh* _mesh, const aiScene* _scene) const
{
	std::vector<Vertex> vertices(_mesh->mNumVertices);
	std::vector<u16> indices;

	for (u32 i = 0; i < _mesh->mNumVertices; ++i)
	{
		vertices[i].pos = glm::vec3{ _mesh->mVertices[i].x, _mesh->mVertices[i].y, _mesh->mVertices[i].z };
		vertices[i].norm = glm::vec3{ _mesh->mNormals[i].x, _mesh->mNormals[i].y, _mesh->mNormals[i].z };

		vertices[i].uv = glm::vec2{ 0.0f };
		if (_mesh->mTextureCoords[0])
		{
			vertices[i].uv = glm::vec2{ _mesh->mTextureCoords[0][i].x, _mesh->mTextureCoords[0][i].y };
		}
	}

	for (u32 i = 0; i < _mesh->mNumFaces; ++i)
	{
		aiFace face = _mesh->mFaces[i];
		for (u32 j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh mesh(vertices, indices);

	if (m_loadMaterials)
	{
		Material& material = processMaterial(_scene->mMaterials[_mesh->mMaterialIndex]);
		mesh.setMaterial(&material);
	}
	else
	{
		mesh.setMaterial(&MaterialsManager::getInstance().getDefaultMaterial());
	}

	return mesh;
}

//-----------------------------------------------------------------------------

Material& ModelCreationHelper::processMaterial(aiMaterial* _material) const
{
	const std::string name = _material->GetName().C_Str();
	if (Material* material = MaterialsManager::getInstance().findMaterial(name))
	{
		LOG_INFO("[ModelCreationHelper] Materil '{}' already exists, returning", name.c_str());
		return *material;
	}

	Material& material = MaterialsManager::getInstance().createMaterial(name);

	material.setShader(*ResourceManager::getInstance().loadShader("res/shaders/composed/MaterialShader.shdata"));

	{
		float shininess = 128.0f;
		_material->Get(AI_MATKEY_SHININESS, shininess);
		material.setProperty("u_specularPower", shininess);
	}
	{
		float opacity = 1.0f;
		_material->Get(AI_MATKEY_OPACITY, opacity);
		material.setProperty("u_opacity", opacity);
	}

	aiColor3D color;
	if (_material->Get(AI_MATKEY_COLOR_AMBIENT, color) == aiReturn_SUCCESS)
	{
		material.setProperty("u_matAmbient", glm::vec3(color.r, color.g, color.b));
	}
	if (_material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == aiReturn_SUCCESS)
	{
		material.setProperty("u_matDiffuse", glm::vec3(color.r, color.g, color.b));
	}
	if (_material->Get(AI_MATKEY_COLOR_SPECULAR, color) == aiReturn_SUCCESS)
	{
		material.setProperty("u_matSpecular", glm::vec3(color.r, color.g, color.b));
	}

	if (_material->GetTextureCount(aiTextureType_DIFFUSE) == 1)
	{
		aiString texturePath;
		_material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

		std::filesystem::path test = std::filesystem::path(m_filePath).parent_path() / texturePath.C_Str();

		Texture* texture = ResourceManager::getInstance().loadTexture(test.string());
		ASSERT(texture);
		if (texture)
		{
			material.setProperty("u_texture2D", *texture);
		}
	}

	return material;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
