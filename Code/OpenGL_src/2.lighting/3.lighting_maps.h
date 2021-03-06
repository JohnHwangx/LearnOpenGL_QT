#pragma once

#include "Shader.h"
#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <iostream>
namespace LIGHTING_MAPS {
	class lighting_maps {
	public:
		lighting_maps();
		~lighting_maps();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		glm::vec3 lightPos;

		static bool firstMouse;
		static float lastX;
		static float lastY;
		static CAMERA::Camera camera;

		void processInput(GLFWwindow* window);
		unsigned int loadTexture(const char* path);
		static void framebuffer_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}