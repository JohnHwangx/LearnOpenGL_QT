#include "1_Create_Triangle.h"
using namespace Create_Triangle;

void createTriangle::show()
{
	/*������������ɫ������*/
	/*������ɫ��*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/*�����ɫ�������Ƿ�ɹ�*/
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error::shader::vertex::compilation_failed\n" << infoLog << std::endl;
	}
	/*Ƭ����ɫ��*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	/*�����ɫ�������Ƿ�ɹ�*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "error::shader::fragment::compilation_failed\n" << infoLog << std::endl;
	}
	/*������ɫ��*/
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/*������Ӵ���*/
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "error::shader::program::link_failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*���ö������ݣ����ö�������*/
	float vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f, -0.5f,0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);//�����������
	glGenBuffers(1, &VBO);//���㻻�ɶ���
						  /*�󶨶�����������ٰ󶨶��㻺�棬�����ö�������*/
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��󻺳����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//����������
	glBindVertexArray(0);

	//while (!glfwWindowShouldClose(window))
	//{
	//	//����
	//	processInput(window);
	//	//��Ⱦ
	//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	//���Ƶ�һ������
	//	glUseProgram(shaderProgram);
	//	glBindVertexArray(VAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	//glfw: �������壬��ѯIO�¼�
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
	//��ѡ������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glfw: ����̨�����֮ǰ����õ�����GLFW��Դ
	//glfwTerminate();
}
