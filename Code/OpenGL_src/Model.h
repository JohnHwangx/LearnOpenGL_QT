#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

namespace MODEL
{
	class Model{
	public:
		Model(char* path);
		void Draw(Shader shader);

	private:
		/*模型数据*/
		std::vector<MESH::Mesh> meshes;
		std::string diretory;
		/*函数*/
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene * scene);
		MESH::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<MESH::Texture> loadMetarialtexture(aiMaterial* mat, aiTextureType* type, std::string typeName);
	};
}