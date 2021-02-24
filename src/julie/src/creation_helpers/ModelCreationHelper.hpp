#pragma once

#include <assimp/material.h>

#include <string_view>
#include <filesystem>
#include <memory>
#include <vector>

struct aiMesh;
struct aiNode;
struct aiScene;
struct aiMaterial;

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

class Mesh;
class Model;
class Texture;
class Shader;
class Material;

class ModelCreationHelper
{
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath, bool _loadMaterials);

//-----------------------------------------------------------------------------
private:
	static std::unique_ptr<Model> loadNfg(std::string_view _filePath);
	static std::unique_ptr<Model> loadAssimp(std::string_view _filePath, bool _loadMaterials);

//-----------------------------------------------------------------------------
	ModelCreationHelper(std::filesystem::path _directoryPath, bool _loadMaterials);
	~ModelCreationHelper();

	void processNode(aiNode* _node, const aiScene* _scene);
	Mesh processMesh(aiMesh* _mesh, const aiScene* _scene) const;
	Material& processMaterial(aiMaterial* _material) const;

	Texture* loadTexture(const aiMaterial* _material, aiTextureType _texType) const;

//-----------------------------------------------------------------------------
	std::vector<Mesh> m_meshes;
	std::filesystem::path m_directory;
	bool m_loadMaterials;

	static const std::string k_colorShaderPath;
	static const std::string k_textureShaderPath;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
