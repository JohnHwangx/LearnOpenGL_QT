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

	Shader shader = Shader("", "");

	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES::vertices_texture), VERTICES::vertices_texture, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES::planeVertices), VERTICES::planeVertices, GL_STATIC_DRAW);
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
