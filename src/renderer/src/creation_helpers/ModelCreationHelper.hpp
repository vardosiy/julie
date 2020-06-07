#pragma once

#include <string_view>
#include <memory>
#include <vector>

struct aiMesh;
struct aiNode;
struct aiScene;

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Mesh;
class Model;

class ModelCreationHelper
{
public:
	static std::unique_ptr<Model> loadFromFile(std::string_view _filePath);

private:
	static std::unique_ptr<Model> loadNfg(std::string_view _filePath);
	static std::unique_ptr<Model> loadAssimp(std::string_view _filePath);

	static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& _meshes);
	static Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
