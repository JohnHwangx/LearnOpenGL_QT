#include "1_Create_Triangle.h"
using namespace Create_Triangle;

void createTriangle::show()
{
	/*创建并编译着色器程序*/
	/*顶点着色器*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/*检查着色器编译是否成功*/
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error::shader::vertex::compilation_failed\n" << infoLog << std::endl;
	}
	/*片段着色器*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/*检查着色器编译是否成功*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "error::shader::fragment::compilation_failed\n" << infoLog << std::endl;
	}
	/*链接着色器*/
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/*检查链接错误*/
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "error::shader::program::link_failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*设置顶点数据，配置顶点属性*/
	float vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f, -0.5f,0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);//顶点数组对象
	glGenBuffers(1, &VBO);//顶点换成对象
						  /*绑定顶点数组对象，再绑定顶点缓存，再配置顶点属性*/
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//解绑缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解绑数组对象
	glBindVertexArray(0);

	//while (!glfwWindowShouldClose(window))
	//{
	//	//输入
	//	processInput(window);
	//	//渲染
	//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	//绘制第一个三角
	//	glUseProgram(shaderProgram);
	//	glBindVertexArray(VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	//glfw: 交换缓冲，轮询IO事件
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
	//可选操作：
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glfw: 控制台，清除之前所获得的所有GLFW资源
	//glfwTerminate();
}
