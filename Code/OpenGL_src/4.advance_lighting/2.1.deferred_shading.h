#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Vertices.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace DEFERRED_SHADING {
	class deferrd_shading {
	public:
		deferrd_shading();
		~deferrd_shading();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		static bool firstMouse;
		static double lastX;
		static double lastY;
		static CAMERA::Camera camera;

		void processInput(GLFWwindow* window);
		void renderQuad();
		void renderCube();

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}