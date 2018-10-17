#include "2.material.h"
#include "Vertices.h"

using namespace std;
using namespace glm;
using namespace MATERIAL;
using namespace VERTICES;

MATERIAL::material::material()
{
	SCR_WIDTH = 1600;
	SCR_HEIGHT = 1600;
}

MATERIAL::material::~material()
{
}

void MATERIAL::material::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window==NULL)
	{
		message.append("Failed to create window.");
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		message.append("Failed to load GLAD.");
		return;
	}

	glEnable(GL_DEPTH_TEST);

	Shader cubeShader("", "");
	Shader lightShader("", "");

	unsigned int cubeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_color), vertices_color, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;

}

void MATERIAL::material::framebuffer_callback(GLFWwindow * window, int width, int height)
{
}

void MATERIAL::material::mouse_callback(GLFWwindow * window, double xPos, double yPos)
{
}

void MATERIAL::material::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
