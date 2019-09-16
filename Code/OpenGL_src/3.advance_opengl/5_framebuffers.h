#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace FRAMEBUFFERS {
	class framebuffers {
	public:
		framebuffers();
		~framebuffers();
		void show(std::string& message);

	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		static bool firstMouse;
		static float lastX;
		static float lastY;
		static CAMERA::Camera camera;

		unsigned int loadTexture(const char* path);
		void processInput(GLFWwindow* window);
		static void framebuffer_callback(GLFWwindow* window, int width, int height);
		static void mousemove_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}