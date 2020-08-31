#include "creation_helpers/ModelCreationHelper.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Mesh.hpp"
#include "julie/Model.hpp"
#include "julie/Material.hpp"

#include "utils/Utils.hpp"

#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

const std::string ModelCreationHelper::k_colorShaderPath = "res/shaders/MaterialColorShader.shdata";
const std::string ModelCreationHelper::k_textureShaderPath = "res/shaders/MaterialTextureShader.shdata";

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadFromFile(std::string_view _filePath, bool _loadMaterials)
{
	std::filesystem::path path(_filePath);

	if (path.extension() == ".nfg")
	{
		return loadNfg(_filePath);
	}
	else
	{
		return loadAssimp(_filePath, _loadMaterials);
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadNfg(std::string_view _filePath)
{
	FILE* pFile = fopen(_filePath.data(), "r");
	ASSERT(pFile);
	if (!pFile)
	{
		return nullptr;
	}

	s32 verticesCount = 0;
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

	std::vector<index_t> indices(indicesCount);
	for (s32 i = 0; i < indicesCount; i += 3)
	{
		fscanf_s(
			pFile, " %*d. %d, %d, %d",
			&indices[i], &indices[i + 1], &indices[i + 2]
		);
	}

	fclose(pFile);

	return std::make_unique<Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

std::unique_ptr<Model> ModelCreationHelper::loadAssimp(std::string_view _filePath, bool _loadMaterials)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_filePath.data(), aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	if (scene && scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE && scene->mRootNode)
	{
		ModelCreationHelper helper(std::filesystem::path(_filePath).parent_path(), _loadMaterials);
		helper.processNode(scene->mRootNode, scene);
		return std::make_unique<Model>(std::move(helper.m_meshes));
	}

	return nullptr;
}

//-----------------------------------------------------------------------------

ModelCreationHelper::ModelCreationHelper(std::filesystem::path _directory, bool _loadMaterials)
	: m_directory(_directory)
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
	auto assimpVecToGlm3 = [](const aiVector3D& _vec) { return glm::vec3{ _vec.x, _vec.y, _vec.z }; };
	auto assimpVecToGlm2 = [](const aiVector3D& _vec) { return glm::vec2{ _vec.x, _vec.y }; };

	std::vector<Vertex> vertices(_mesh->mNumVertices);
	std::vector<index_t> indices;

	for (u32 i = 0; i < _mesh->mNumVertices; ++i)
	{
		ASSERT(_mesh->mVertices);
		ASSERT(_mesh->mTangents);
		ASSERT(_mesh->mBitangents);

		vertices[i].pos			= assimpVecToGlm3(_mesh->mVertices[i]);
		vertices[i].tangent		= assimpVecToGlm3(_mesh->mTangents[i]);
		vertices[i].bitangent	= assimpVecToGlm3(_mesh->mBitangents[i]);
		vertices[i].norm		= _mesh->mNormals			? assimpVecToGlm3(_mesh->mNormals[i])			: glm::vec3{ 0.0f };
		vertices[i].uv			= _mesh->mTextureCoords[0]	? assimpVecToGlm2(_mesh->mTextureCoords[0][i])	: glm::vec2{ 0.0f };
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

	return mesh;
}

//-----------------------------------------------------------------------------

Material& ModelCreationHelper::processMaterial(aiMaterial* _material) const
{
	MaterialsManager& materialsMgr = MaterialsManager::getInstance();
	const std::string name = _material->GetName().C_Str();

	if (Material* material = materialsMgr.findMaterial(name))
	{
		LOG_INFO("[ModelCreationHelper] Material '{}' already exists, returning", name.c_str());
		return *material;
	}

	Material& material = materialsMgr.createMaterial(name);

	{
		float shininess = 128.0f;
		_material->Get(AI_MATKEY_SHININESS, shininess);
		material.setProperty("u_shininess", shininess);
	}
	{
		float opacity = 1.0f;
		_material->Get(AI_MATKEY_OPACITY, opacity);
		material.setProperty("u_opacity", opacity);
	}
	{
		aiColor3D ambient;
		aiColor3D diffuse;
		aiColor3D specular;

		_material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		_material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

		material.setProperty("u_matAmbient", glm::vec3(ambient.r, ambient.g, ambient.b));
		material.setProperty("u_matDiffuse", glm::vec3(diffuse.r, diffuse.g, diffuse.b));
		material.setProperty("u_matSpecular", glm::vec3(specular.r, specular.g, specular.b));
	}
	{
		Texture* diffuseTexture = loadTexture(_material, aiTextureType_DIFFUSE);
		material.setProperty("u_texDiffuse", diffuseTexture);


		const std::string& shaderPath = diffuseTexture ? k_textureShaderPath : k_colorShaderPath;
		material.setShader(ResourceManager::getInstance().loadShader(shaderPath));
	}

	material.setProperty("u_texNormals", loadTexture(_material, aiTextureType_HEIGHT));

	return material;
}

//-----------------------------------------------------------------------------

Texture* ModelCreationHelper::loadTexture(const aiMaterial* _material, aiTextureType _texType) const
{
	Texture* texture = nullptr;
	if (_material->GetTextureCount(_texType) == 1)
	{
		aiString textureName;
		_material->GetTexture(_texType, 0, &textureName);

		std::filesystem::path texturePath = m_directory / textureName.C_Str();
		texture = ResourceManager::getInstance().loadTexture(texturePath.generic_string());
		ASSERT(texture);
	}
	return texture;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
