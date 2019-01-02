// OpenGL_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <1.getting_start/3.1.shaders_uniform.h>
#include <2.lighting/1.base_lighting.h>
#include <2.lighting/3.lighting_maps.h>
#include <2.lighting/4.light_caster.h>
#include <2.lighting/6.model_loading.h>

#include <3.advance_opengl/1.depth_testing.h>

int main()
{
	/*Shader_Uniform::shader_uniform show;*/

	std::string message;
	/*BASE_LIGHT::base_light show = BASE_LIGHT::base_light();*/

	//LIGHTING_MAPS::lighting_maps show;

	//LIGHT_CASTER::light_caster show;

	//MODEL_LOADING::model_loading show;

	DEPTH_TESTING::depth_testing show;
	show.show(message);
    return 0;
}

