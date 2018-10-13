#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <iostream>

namespace Textures
{
	class textures
	{
	public:
		textures();
		void show(std::string& message);
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 800;

		static void framebuffer_size_callback(GLFWwindow* window, int x, int y);
		void processInput(GLFWwindow* window);
	};
}