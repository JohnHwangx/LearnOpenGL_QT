#include "3.lighting_maps.h"

#include "Vertices.h"

using namespace std;
using namespace glm;
using namespace LIGHTING_MAPS;

bool lighting_maps::firstMouse = true;
float lighting_maps::lastX = 0.0f;
float lighting_maps::lastY = 0.0f;
CAMERA::Camera lighting_maps::camera = vec3(0.0f, 0.0f, 3.0f);

LIGHTING_MAPS::lighting_maps::lighting_maps()
{
	SCR_WIDTH = 1200;
	SCR_HEIGHT = 1200;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	lightPos = vec3(1.2f, 1.0f, 2.0f);

	firstMouse = true;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0;
	camera = vec3(0.0f, 0.0f, 3.0f);
}

LIGHTING_MAPS::lighting_maps::~lighting_maps()
{
}

void lighting_maps::show(std::string & message)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		message.append("Failed to load GLAD.");
		return;
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

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture("../../Resource/container2.png");
	unsigned int specularMap = loadTexture("../../Resource/container2_specular.png");

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

		//cube
		cubeShader.use();

		vec3 lightColor;
		lightColor.x = sin(glfwGetTime()*0.5f);
		lightColor.y = sin(glfwGetTime()*0.7f);
		lightColor.z = sin(glfwGetTime()*1.3f);
		vec3 diffuseColor = lightColor * vec3(0.5f);
		vec3  ambientColor = diffuseColor * vec3(0.2f);

		/*cubeShader.setVec3("light.material", 0.2f, 0.2f, 0.2f);
		cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);*/
		cubeShader.setVec3("light.material", ambientColor);
		cubeShader.setVec3("light.diffuse", diffuseColor);
		cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		cubeShader.setVec3("light.position", lightPos);

		/*cubeShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		cubeShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		cubeShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);*/
		cubeShader.setFloat("material.shininess", 64.0f);

		cubeShader.setVec3("viewPos", camera.Position);

		mat4 projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);

		mat4 model;
		cubeShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//lamp
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		model = translate(model, lightPos);
		model = scale(model, vec3(0.2));
		lightShader.setMat4("model", model);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

void LIGHTING_MAPS::lighting_maps::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CAMERA::RIGHT, deltaTime);
}

unsigned int lighting_maps::loadTexture(const char * path)
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

void LIGHTING_MAPS::lighting_maps::framebuffer_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void LIGHTING_MAPS::lighting_maps::mouse_callback(GLFWwindow * window, double xPos, double yPos)
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

void LIGHTING_MAPS::lighting_maps::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
