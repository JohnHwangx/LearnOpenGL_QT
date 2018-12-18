#include "1.depth_testing.h"
using namespace DEPTH_TESTING;
using namespace std;

DEPTH_TESTING::depth_testing::depth_testing()
{
}

DEPTH_TESTING::depth_testing::~depth_testing()
{
}

void DEPTH_TESTING::depth_testing::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Depth_Testing", NULL, NULL);
	if (window == NULL) {
		message.append("Failed to create window.");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);
	glfwSetCursorPosCallback(window, mousemove_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		message.append("Failed to load GLAD!");
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	Shader shader("", "");

	unsigned int cubeVAO, cubeVBO;

}

void DEPTH_TESTING::depth_testing::framebuffer_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void DEPTH_TESTING::depth_testing::mousemove_callback(GLFWwindow * window, double xpos, double ypos)
{
}

void DEPTH_TESTING::depth_testing::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
