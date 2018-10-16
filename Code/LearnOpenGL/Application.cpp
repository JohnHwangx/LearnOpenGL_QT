#include "Application.h"
//#include <1.getting_start/7.3.camera_mouse_zoom.h>

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.shader_uniform, &QPushButton::clicked, this, &Application::on_shader_uniform);
	connect(ui.texture, &QPushButton::clicked, this, &Application::on_texture);
	connect(ui.camera, &QPushButton::clicked, this, &Application::on_camera);
	connect(ui.basic_lighting, &QPushButton::clicked, this, &Application::on_base_light);
}

void Application::on_shader_uniform()
{
	Shader_Uniform::shader_uniform show;
	show.show();
}

void Application::on_texture()
{
	std::string message;
	Textures::textures show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_camera()
{
	std::string message;
	Camera::camera show= Camera::camera();
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_base_light()
{
	std::string message;
	BASE_LIGHT::base_light show = BASE_LIGHT::base_light();
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}
