#pragma once
//#include "1.»Î√≈/3.1.shaders_uniform.h"
//#include "1.getting_start/3.1.shaders_uniform.h"
#include <1.getting_start/3.1.shaders_uniform.h>
#include <1.getting_start/4.1.textures.h>
#include <1.getting_start/7.3.camera.h>
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
};
