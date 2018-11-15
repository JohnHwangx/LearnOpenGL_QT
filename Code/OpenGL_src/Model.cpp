#include "Model.h"

using namespace Assimp;

MODEL::Model::Model(char * path)
{
}

void MODEL::Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void MODEL::Model::loadModel(std::string path)
{
	
}

void MODEL::Model::processNode(aiNode * node, const aiScene * scene)
{
}

MESH::Mesh MODEL::Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	return MESH::Mesh();
}

std::vector<MESH::Texture> MODEL::Model::loadMetarialtexture(aiMaterial * mat, aiTextureType * type, std::string typeName)
{
	return std::vector<MESH::Texture>();
}
