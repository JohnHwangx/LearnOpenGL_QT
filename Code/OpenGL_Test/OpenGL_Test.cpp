// OpenGL_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <1.getting_start/3.1.shaders_uniform.h>
#include <2.lighting/1.base_lighting.h>

int main()
{
	/*Shader_Uniform::shader_uniform show;
	show.show();*/

	std::string message;
	BASE_LIGHT::base_light show = BASE_LIGHT::base_light();
	show.show(message);
    return 0;
}

