#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Vertices.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

namespace HDR {
	class hdr {
	public:
		hdr();
		~hdr();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;
		bool isHdr;
		bool hdrKeyPressed;
		float exposure;

		float deltaTime;
		float lastFrame;

		static bool firstMouse;
		static double lastX;
		static double lastY;
		static CAMERA::Camera camera;

		void processInput(GLFWwindow* window);
		void renderQuad();
		void renderCube();
		unsigned int loadTexture(char const * path, bool gammaCorrection);

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}