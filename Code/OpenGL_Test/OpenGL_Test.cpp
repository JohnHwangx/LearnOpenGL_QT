// OpenGL_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <1.getting_start/3.1.shaders_uniform.h>
#include <2.lighting/1.base_lighting.h>
#include <2.lighting/3.lighting_maps.h>
#include <2.lighting/4.light_caster.h>

int main()
{
	/*Shader_Uniform::shader_uniform show;*/

	std::string message;
	/*BASE_LIGHT::base_light show = BASE_LIGHT::base_light();*/

	//LIGHTING_MAPS::lighting_maps show;

	LIGHT_CASTER::light_caster show;
	show.show(message);
    return 0;
}

