#include "2.material.h"
#include "Vertices.h"

using namespace std;
using namespace glm;
using namespace MATERIAL;
using namespace VERTICES;
using namespace CAMERA;

Camera material::camera = Camera(vec3(0.0f, 0.0f, 0.3f));

MATERIAL::material::material()
{
	SCR_WIDTH = 1600;
	SCR_HEIGHT = 1600;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	camera = Camera(vec3(0.0f, 0.0f, 0.3f));
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
	if (window == NULL)
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
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_color), vertices_color, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeShader.use();
		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);

		mat4 model;
		cubeShader.setMat4("model", model);
	}
}

void MATERIAL::material::processInput(GLFWwindow * window)
{
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
