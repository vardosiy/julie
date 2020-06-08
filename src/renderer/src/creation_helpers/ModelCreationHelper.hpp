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

private:
	static std::unique_ptr<Model> loadNfg(std::string_view _filePath);
	static std::unique_ptr<Model> loadAssimp(std::string_view _filePath, bool _loadMaterials);

	static void processNode(aiNode* _node, const aiScene* _scene, std::vector<Mesh>& _meshes, bool _loadMaterials);
	static Mesh processMesh(aiMesh* _mesh, const aiScene* _scene, bool _loadMaterials);
	static Material& processMaterial(aiMaterial* _material);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
