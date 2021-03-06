#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Vertices.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace MODEL_LOADING {
	class model_loading {
	public:
		model_loading();
		~model_loading();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTiem;
		float lastFrame;

		static bool firstMouse;
		static double lastX;
		static double lastY;
		static CAMERA::Camera camera;

		void processInput(GLFWwindow* window);
		static void framesize_callback(GLFWwindow* window, int width, int height);
		static void cursorpos_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}