#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <iostream>

namespace CAMERA_MOUSE_ZOOM
{
	using namespace glm;
	class camera_mouse_zoom
	{
	public:
		camera_mouse_zoom();
		void show();
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 800;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		static bool firstMouse;
		static float yaw;
		static float pitch;
		static float lastX;
		static float lastY;
		static float fov;

		vec3 cameraPos = vec3(0.0f, 0.0f,3.0f);
		static vec3 cameraFront;
		vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

		static void framebuffer_size_callback(GLFWwindow* window, int x, int y);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scoll__callback(GLFWwindow* window, double xoffset, double yoffset);
		void processInput(GLFWwindow* window);
	};
}