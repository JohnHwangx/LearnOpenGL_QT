#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Shader_Uniform
{
	class shader_uniform
	{
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
								uniform vec4 ourColor;\n \
								void main()\n \
								{\n \
									FragColor = ourColor;\n \
								}\n ";
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 800;

		void processInput(GLFWwindow* window);

		void static framebuffer_size_callback(GLFWwindow* window, int width, int height);

	public:
		void show();
	};
}