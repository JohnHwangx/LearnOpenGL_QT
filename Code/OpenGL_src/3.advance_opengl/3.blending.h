#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace BLENDING {
	class blending {
	public:
		blending();
		~blending();
		void show(std::string &message);
	private:
		unsigned int SCR_WIDTH, SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		static float lastX;
		static float lastY;
		static bool firstmouse;
		static CAMERA::Camera camera;

		unsigned int loadTexture(const char* path);
		void processInput(GLFWwindow* window);
		static void framebuffer_callback(GLFWwindow* window, int width, int height);
		static void mousemove_callback(GLFWwindow* window, double posx, double posy);
		static void scroll_callback(GLFWwindow* window, double offsetx, double offsety);
	};
}