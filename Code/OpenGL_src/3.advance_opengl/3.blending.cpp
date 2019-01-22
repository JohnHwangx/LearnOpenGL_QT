#include "3.blending.h"

using namespace std;

BLENDING::blending::blending()
{
}

BLENDING::blending::~blending()
{
}

void BLENDING::blending::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"Blending",NULL,NULL);
	if (window == NULL) {
		cout << "failed to create window." << endl;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_callback);
	glfwSetCursorPosCallback(window, mousemove_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "failed to load GLAD.";
	}



}

void BLENDING::blending::processInput(GLFWwindow * window)
{
}

void BLENDING::blending::framebuffer_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void BLENDING::blending::mousemove_callback(GLFWwindow * window, double posx, double posy)
{
	if (firstmouse) {
		lastX = posx;
		lastY = posy;
		firstmouse = false;
	}

	float xoffset = posx - lastX;
	float yoffset = lastY - posy;

	lastX = posx;
	lastY = posy;

	camera.ProcessMouseMove(xoffset, yoffset);
}

void BLENDING::blending::scroll_callback(GLFWwindow * window, double offsetx, double offsety)
{
	camera.ProcessMouseScroll(offsety);
}
