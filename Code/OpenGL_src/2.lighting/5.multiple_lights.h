#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
namespace MULTIPLE_LIGHTS {
	class multiple_lights {
	public:
		multiple_lights();
		~multiple_lights();
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

		unsigned int loadTexture(const char* path, std::string & message);
		void processInput(GLFWwindow * window);
		static void framesize_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}