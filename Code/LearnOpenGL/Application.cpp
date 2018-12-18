#include "Application.h"
//#include <1.getting_start/7.3.camera_mouse_zoom.h>

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ÈëÃÅ
	connect(ui.shader_uniform, &QPushButton::clicked, this, &Application::on_shader_uniform);
	connect(ui.texture, &QPushButton::clicked, this, &Application::on_texture);
	//¹âÕÕ
	connect(ui.camera, &QPushButton::clicked, this, &Application::on_camera);
	connect(ui.basic_lighting, &QPushButton::clicked, this, &Application::on_base_light);
	connect(ui.material, &QPushButton::clicked, this, &Application::on_material);
	connect(ui.lighting_map, &QPushButton::clicked, this, &Application::on_lighting_maps);
	connect(ui.light_caster, &QPushButton::clicked, this, &Application::on_light_caster);
	connect(ui.multiple_lights, &QPushButton::clicked, this, &Application::on_multiple_light);
	connect(ui.model_loading, &QPushButton::clicked, this, &Application::on_model_loading);
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

void Application::on_material()
{
	std::string message;
	MATERIAL::material show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_lighting_maps()
{
	std::string message;
	LIGHTING_MAPS::lighting_maps show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_light_caster()
{
	std::string message;
	LIGHT_CASTER::light_caster show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_multiple_light()
{
	std::string message;
	MULTIPLE_LIGHTS::multiple_lights show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}

void Application::on_model_loading()
{
	std::string message;
	MODEL_LOADING::model_loading show;
	show.show(message);
	ui.textBrowser->setText(QString::fromStdString(message));
}
