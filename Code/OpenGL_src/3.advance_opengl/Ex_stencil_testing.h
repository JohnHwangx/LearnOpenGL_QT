#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Ex_STENCIL_TESTING
{
	class ex_stencil_testing
	{
	public:
		ex_stencil_testing();
		~ex_stencil_testing();
		void show(std::string& message);

	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		unsigned int loadTexture(const char* path);
		void processInput(GLFWwindow* window);
		static void framebuffer_callback(GLFWwindow* window, int width, int height);
	};
}