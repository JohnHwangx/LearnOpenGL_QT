#include "1.base_lighting.h"

BASE_LIGHT::base_light::base_light()
{
}

BASE_LIGHT::base_light::~base_light()
{
}

void BASE_LIGHT::base_light::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		message.append("Failed to create window");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framesize_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		message.append("Failed to load GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);

	Shader cubeShader("../OpenGL_src/2.lighting/1.base_lighting.vert", 
		"../OpenGL_src/2.lighting/1.base_lighting.frag");

	float* vertices = VERTICES::vertices_color;

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void BASE_LIGHT::base_light::framesize_callback(GLFWwindow * window, int weight, int height)
{
	glViewport(0, 0, weight, height);
}

void BASE_LIGHT::base_light::mouse_callback(GLFWwindow * window, double xPos, double yPos)
{
}

void BASE_LIGHT::base_light::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
