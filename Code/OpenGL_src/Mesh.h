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
		std::string path;// ���Ǵ��������·������������������бȽ�
	};

	class Mesh {
	public:
		/*��������*/
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		/*����*/
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();
		void Draw(Shader shader);
	private:
		/*��Ⱦ��*/
		unsigned int VAO, VBO, EBO;
		/*����*/
		void setupMesh();
	};
}