#include "Application.h"

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.shader_uniform, &QPushButton::clicked, this, &Application::on_shader_uniform);
	connect(ui.texture, &QPushButton::clicked, this, &Application::on_texture);
}

void Application::on_shader_uniform()
{
	Shader_Uniform::shader_uniform show;
	show.show();
}

void Application::on_texture()
{
	Textures::textures show;
	show.show();
}
