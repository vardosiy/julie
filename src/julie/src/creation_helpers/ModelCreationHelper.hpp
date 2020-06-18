#pragma once

#include <string_view>
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
	ModelCreationHelper(std::string_view _filePath, bool _loadMaterials);
	~ModelCreationHelper();

	void processNode(aiNode* _node, const aiScene* _scene);
	Mesh processMesh(aiMesh* _mesh, const aiScene* _scene) const;
	Material& processMaterial(aiMaterial* _material) const;

//-----------------------------------------------------------------------------
	std::vector<Mesh> m_meshes;
	std::string_view m_filePath;
	bool m_loadMaterials;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
