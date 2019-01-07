#include "Ex_stencil_testing.h"

using namespace glm;
using namespace std;
using namespace Ex_STENCIL_TESTING;

ex_stencil_testing::ex_stencil_testing()
{
}

ex_stencil_testing::~ex_stencil_testing()
{
}

void ex_stencil_testing::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Depth_Testing", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);
	//glfwSetCursorPosCallback(window, mousemove_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	Shader cubeShader("../OpenGL_src/2.lighting/shaders/3.lighting_maps.vert",
		"../OpenGL_src/2.lighting/shaders/3.lighting_maps.frag");
	Shader lightShader("../OpenGL_src/2.lighting/shaders/1.1.lamp.vert",
		"../OpenGL_src/2.lighting/shaders/1.1.lamp.frag");

	unsigned int cubeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES::vertices_normal_texture), VERTICES::vertices_normal_texture, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	unsigned int kittyTex = loadTexture("../../Resource/Kitty.png");
	unsigned int puppyTex = loadTexture("../../Resource/puppy.png");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, kittyTex);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, puppyTex);

		cubeShader.use();

		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		cubeShader.setMat4("projection", projection);
		mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("view", view);

	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

unsigned int ex_stencil_testing::loadTexture(const char * path)
{
	unsigned int textureId;
	glGenTextures(1, &textureId);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format == GL_RGB;
		else if (nrChannels = 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	return textureId;
}

void ex_stencil_testing::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void ex_stencil_testing::framebuffer_callback(GLFWwindow * window, int width, int height)
{
}

void ex_stencil_testing::mousemove_callback(GLFWwindow * window, double xPos, double yPos)
{
}

void ex_stencil_testing::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
