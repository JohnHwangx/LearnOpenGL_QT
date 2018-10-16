#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
namespace BASE_LIGHT {
	class base_light {
	public:
		base_light();
		~base_light();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		static bool firstMouse;
		static Camera camera;
		static float lastX;
		static float lastY;

		glm::vec3 lightPos;

		void processInput(GLFWwindow* window);
		static void framesize_callback(GLFWwindow* window, int weight, int height);
		static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}