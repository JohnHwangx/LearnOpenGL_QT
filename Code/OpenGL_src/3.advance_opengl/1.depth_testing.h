#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace DEPTH_TESTING
{
	class depth_testing {
	public:
		depth_testing();
		~depth_testing();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		static void framebuffer_callback(GLFWwindow* window, int width, int height);
		static void mousemove_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}