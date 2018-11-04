#include "5.multiple_lights.h"

using namespace glm;
using namespace std;
using namespace MULTIPLE_LIGHTS;

bool multiple_lights::firstMouse = true;;
float multiple_lights::lastX = 0.0f;
float multiple_lights::lastY = 0.0f;
CAMERA::Camera multiple_lights::camera = vec3(0.0f, 0.0f, 3.0f);

MULTIPLE_LIGHTS::multiple_lights::multiple_lights()
{
	SCR_WIDTH = 1200;
	SCR_HEIGHT = 1200;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	firstMouse = true;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
	camera = vec3(0.0f, 0.0f, 3.0f);
}

MULTIPLE_LIGHTS::multiple_lights::~multiple_lights()
{
}

void MULTIPLE_LIGHTS::multiple_lights::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		message.append("Failed to load GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);

	Shader cubeShader("../OpenGL_src/2.lighting/shaders/5.multiple_lights.vert",
		"../OpenGL_src/2.lighting/shaders/5.multiple_lights.frag");
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture("../../Resource/container2.png", message);
	unsigned int specularMap = loadTexture("../../Resource/container2_specular.png", message);

	cubeShader.use();
	cubeShader.setInt("material.diffuse", 0);
	cubeShader.setInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeShader.use();
		cubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		cubeShader.setFloat("light.constant", 1.0f);
		cubeShader.setFloat("light.linear", 0.09f);
		cubeShader.setFloat("light.quadratic", 0.032f);

		cubeShader.setFloat("light.cutOff", cos(radians(12.5f)));
		cubeShader.setFloat("light.outerCutOff", cos(radians(17.5f)));
		cubeShader.setVec3("light.position", camera.Position);
		cubeShader.setVec3("light.direction", camera.Front);

		cubeShader.setFloat("material.shininess", 32.0f);
		cubeShader.setVec3("viewPos", camera.Position);

		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		cubeShader.setMat4("projection", projection);
		mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("view", view);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			mat4 model;
			model = translate(model, VERTICES::cubePositions[i]);
			float angle = 20.0*i;
			model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
			cubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			mat4 model;
			model = translate(model, VERTICES::pointLightPositions[i]);
			model = scale(model, vec3(0.2f));
			lightShader.setMat4("mdoel", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightShader);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

unsigned int MULTIPLE_LIGHTS::multiple_lights::loadTexture(const char * path, std::string & message)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChennal;
	unsigned char* data = stbi_load(path, &width, &height, &nrChennal, 0);
	if (data)
	{
		GLenum format;
		if (nrChennal == 1)
			format = GL_RED;
		else if (nrChennal == 3)
			format = GL_RGB;
		else if (nrChennal == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		message.append("Faile to create Texture");
	}
	stbi_image_free(data);

	return textureID;
}

void MULTIPLE_LIGHTS::multiple_lights::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::LEFT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::RIGHT, deltaTime);
}

void MULTIPLE_LIGHTS::multiple_lights::framesize_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MULTIPLE_LIGHTS::multiple_lights::mouse_callback(GLFWwindow * window, double xPos, double yPos)
{
	if (firstMouse)
	{
		firstMouse = false;
		lastX = xPos;
		lastY = yPos;
	}
	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMove(xoffset, yoffset);
}

void MULTIPLE_LIGHTS::multiple_lights::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
