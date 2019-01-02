#pragma once
#include <1.getting_start/3.1.shaders_uniform.h>
#include <1.getting_start/4.1.textures.h>
#include <1.getting_start/7.3.camera.h>

#include <2.lighting/1.base_lighting.h>
#include <2.lighting/2.material.h>
#include <2.lighting/3.lighting_maps.h>
#include <2.lighting/4.light_caster.h>
#include <2.lighting/5.multiple_lights.h>
#include <2.lighting/6.model_loading.h>

#include <3.advance_opengl/1.depth_testing.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include "ui_Application.h"

class Application : public QMainWindow
{
	Q_OBJECT

public:
	Application(QWidget *parent = Q_NULLPTR);

private:
	Ui::ApplicationClass ui;

private slots:
	void on_shader_uniform();
	void on_texture();
	void on_camera();

	void on_base_light();
	void on_material();
	void on_lighting_maps();
	void on_light_caster();
	void on_multiple_light();
	void on_model_loading();

	void on_depth_testing();
};
