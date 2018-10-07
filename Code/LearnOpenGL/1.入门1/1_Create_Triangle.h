#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Create_Triangle
{
	using namespace std;

	class createTriangle {
	public:
		void show();

	private:
		//顶点着色器
		const char *vertexShaderSource = "#version 330 core\n \
								layout (location=0) in vec3 aPos;\n \
								void main()\n \
								{\n \
									gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0);\n \
								}\n ";
		//片段着色器
		const char *fragmentShaderSource = "#version 330 core\n  \
								out vec4 FragColor;\n \
								void main()\n \
								{\n \
									FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n \
								}\n ";
	};
}