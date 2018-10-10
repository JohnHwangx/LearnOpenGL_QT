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
		void show();
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 800;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		bool firstMouse = true;
		float yaw = -90.0f;
		float pitch = 0.0f;
		float lastX = SCR_WIDTH / 2.0;
		float lastY = SCR_HEIGHT / 2.0;
		float fov = 45.0f;

		vec3 cameraPos = vec3(0.0f, 0.0f,3.0f);
		vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
		vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

		static void framebuffer_size_callback(GLFWwindow* window, int x, int y);
		void processInput(GLFWwindow* window);
	};
}