#pragma once

#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include <iostream>
#include <vector>

namespace MODEL
{
	class Model{
	public:
		Model(const char* path);
		void Draw(Shader shader);

	private:
		/*模型数据*/
		std::vector<MESH::Mesh> meshes;
		std::string directory;
		std::vector<MESH::Texture> textures_loaded;
		/*函数*/
		void loadModel(const std::string& path);
		void processNode(aiNode *node, const aiScene * scene);
		MESH::Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<MESH::Texture> loadMetarialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

		unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma=false);
	};
}