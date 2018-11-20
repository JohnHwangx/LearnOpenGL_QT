#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace MESH {
	struct Vertex {
		glm::vec3 Postion;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 BiTangent;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;// 我们储存纹理的路径用于与其它纹理进行比较
	};

	class Mesh {
	public:
		/*网格数据*/
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		/*函数*/
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();
		void Draw(Shader shader);
	private:
		/*渲染器*/
		unsigned int VAO, VBO, EBO;
		/*函数*/
		void setupMesh();
	};
}