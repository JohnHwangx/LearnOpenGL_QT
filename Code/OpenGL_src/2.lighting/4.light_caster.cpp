#include "4.light_caster.h"

using namespace glm;
using namespace std;
using namespace LIGHT_CASTER;

bool light_caster::firstMouse = true;
float light_caster::lastX = 0.0f;
float light_caster::lastY = 0.0f;
CAMERA::Camera light_caster::camera = vec3(0.0f, 0.0f, 3.0f);

LIGHT_CASTER::light_caster::light_caster()
{
	SCR_WIDTH = 1200;
	SCR_HEIGHT = 1200;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	lightPos = vec3(1.2f, 1.0f, 2.0f);

	firstMouse = true;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
	camera = vec3(0.0f, 0.0f, 3.0f);
}

LIGHT_CASTER::light_caster::~light_caster()
{
}

void LIGHT_CASTER::light_caster::show(std::string & message)
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

	Shader cubeShader("../OpenGL_src/2.lighting/shaders/4.light_caster.vert",
		"../OpenGL_src/2.lighting/shaders/4.light_caster.frag");
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

	unsigned int diffuseTex = loadTexture("../../Resource/container2.png", message);
	unsigned int specularTex = loadTexture("../../Resource/container2_specular.png", message);

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
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		cubeShader.use();
		cubeShader.setVec3("lighting.ambient", 0.2f, 0.2f, 0.2f);
		cubeShader.setVec3("lighting.diffuse", 0.5f, 0.5f, 0.5f);
		cubeShader.setVec3("lighting.specular", 1.0f, 1.0f, 1.0f);

		cubeShader.setFloat("lighting.constant", 1.0f);
		cubeShader.setFloat("lighting.linear", 0.09f);
		cubeShader.setFloat("lighting.quadratic", 0.032f);

		//cubeShader.setVec3("lighting.position", lightPos);
		//cubeShader.setVec3("lighting.direction", -2.0f, -1.0f, -0.3f);
		cubeShader.setVec3("lighting.position", camera.Position);
		cubeShader.setVec3("lighting.direction", camera.Front);
		cubeShader.setFloat("lighting.cutOff", glm::cos(glm::radians(12.5f)));
		cubeShader.setFloat("lighting.outerCutOff", glm::cos(glm::radians(17.5f)));

		cubeShader.setFloat("material.shininess", 64.0f);
		cubeShader.setVec3("viewPos", camera.Position);

		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);

		/*mat4 model;
		cubeShader.setMat4("model", model);*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTex);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTex);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			mat4 model;
			model = translate(model, VERTICES::cubePositions[i]);
			float angle = 20.0f * i;
			model = rotate(model, radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*mat4 model;
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		model = translate(model, lightPos);
		model = scale(model, vec3(0.2));
		lightShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

unsigned int LIGHT_CASTER::light_caster::loadTexture(const char * path, std::string& message)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);

	int width, height, nrChannel;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);
	if (data)
	{
		GLenum format;
		if (nrChannel == 1)
			format = GL_RED;
		else if (nrChannel == 3)
			format = GL_RGB;
		else  if (nrChannel == 4)
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
		message.append("Failed to generate Texture");
	}
	stbi_image_free(data);

	return textureID;
}

void LIGHT_CASTER::light_caster::processInput(GLFWwindow * window)
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

void LIGHT_CASTER::light_caster::framesize_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void LIGHT_CASTER::light_caster::mouse_callback(GLFWwindow * window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMove(xoffset, yoffset);
}

void LIGHT_CASTER::light_caster::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
