#pragma 
#include "Shader.h"
//#include "Vertices.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
namespace MATERIAL {
	class material {
	public:
		material();
		~material();
		void show(std::string& message);
	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;

		float deltaTime;
		float lastFrame;

		static CAMERA::Camera camera;

		void processInput(GLFWwindow* window);
		static void framebuffer_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}