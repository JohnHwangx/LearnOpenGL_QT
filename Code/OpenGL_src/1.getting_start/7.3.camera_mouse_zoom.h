#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace CAMERA_MOUSE_ZOOM
{
	class camera_mouse_zoom
	{
	public:
		void show();
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 800;

		static void framebuffer_size_callback(GLFWwindow* window, int x, int y);
		void processInput(GLFWwindow* window);
	};
}