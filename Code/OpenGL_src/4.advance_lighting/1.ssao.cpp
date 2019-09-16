#include "1.ssao.h"
using namespace std;
using namespace glm;
using namespace MODEL;
using namespace SSAO;

bool ssao::firstMouse = true;
double ssao::lastX;
double ssao::lastY;
CAMERA::Camera ssao::camera;

bool keys[1024];
bool keysPressed[1024];

SSAO::ssao::ssao()
{
	SCR_WIDTH = 1200;
	SCR_HEIGHT = 1200;

	deltaTiem = 0.0f;
	lastFrame = 0.0f;

	firstMouse = true;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
	camera = vec3(0.0f, 0.0f, 3.0f);
}

SSAO::ssao::~ssao()
{
}

void SSAO::ssao::show(std::string& message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Model_Loading", NULL, NULL);
	if (window == NULL)
	{
		message.append("Failed to create Window.");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetFramebufferSizeCallback(window, framesize_callback);
	glfwSetCursorPosCallback(window, cursorpos_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		message.append("Failed to load GLAD.");
		return;
	}

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	// Setup and compile our shaders
	Shader shaderGeometryPass("../OpenGL_src/4.advance_lighting/shaders/1_ssao_geometry.vert",
		"../OpenGL_src/4.advance_lighting/shaders/1_ssao_geometry.frag");
	Shader shaderLightingPass("../OpenGL_src/4.advance_lighting/shaders/1_ssao.vert", 
		"../OpenGL_src/4.advance_lighting/shaders/1_ssao_lighting.frag");
	Shader shaderSSAO("../OpenGL_src/4.advance_lighting/shaders/1_ssao.vert",
		"../OpenGL_src/4.advance_lighting/shaders/1_ssao.frag");
	Shader shaderSSAOBlur("../OpenGL_src/4.advance_lighting/shaders/1_ssao.vert",
		"../OpenGL_src/4.advance_lighting/shaders/1_ssao_blur.frag");

	// Set samplers
	shaderLightingPass.use();
	glUniform1i(glGetUniformLocation(shaderLightingPass.Program, "gPositionDepth"), 0);
	glUniform1i(glGetUniformLocation(shaderLightingPass.Program, "gNormal"), 1);
	glUniform1i(glGetUniformLocation(shaderLightingPass.Program, "gAlbedo"), 2);
	glUniform1i(glGetUniformLocation(shaderLightingPass.Program, "ssao"), 3);
	shaderSSAO.Use();
	glUniform1i(glGetUniformLocation(shaderSSAO.Program, "gPositionDepth"), 0);
	glUniform1i(glGetUniformLocation(shaderSSAO.Program, "gNormal"), 1);
	glUniform1i(glGetUniformLocation(shaderSSAO.Program, "texNoise"), 2);

	MODEL::Model modelLoader("../../Resource/nanosuit/nanosuit.obj");

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTiem = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		mat4 model;
		model = translate(model, vec3(0.0f, -1.75f, 0.0f));
		model = scale(model, vec3(0.2f, 0.2f, 0.2f));
		shader.setMat4("model", model);
		modelLoader.Draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void SSAO::ssao::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::FORWARD, deltaTiem);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::BACKWARD, deltaTiem);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::LEFT, deltaTiem);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::RIGHT, deltaTiem);
}

void SSAO::ssao::framesize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void SSAO::ssao::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
			keysPressed[key] = false;
		}
	}
}

void SSAO::ssao::cursorpos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	double xoffset = lastX - xpos;
	double yoffset = ypos - lastY;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(xoffset, yoffset);
}

void SSAO::ssao::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
