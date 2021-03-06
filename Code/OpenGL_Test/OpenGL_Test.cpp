// OpenGL_Test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <1.getting_start/3.1.shaders_uniform.h>
#include <2.lighting/1.base_lighting.h>
#include <2.lighting/3.lighting_maps.h>
#include <2.lighting/4.light_caster.h>
#include <2.lighting/6.model_loading.h>

#include <3.advance_opengl/1.depth_testing.h>
#include <3.advance_opengl/2.stencil_testing.h>
#include <3.advance_opengl/Ex_stencil_testing.h>
#include <3.advance_opengl/5_framebuffers.h>
#include <3.advance_opengl/5_1_postprocessing.h>

#include <4.advance_lighting/1.ssao.h>
#include <4.advance_lighting/2.1.deferred_shading.h>
#include <4.advance_lighting/2.2.deferred_shading_volumes.h>
#include <4.advance_lighting/6.hdr.h>

int main()
{
	/*Shader_Uniform::shader_uniform show;*/

	std::string message;
	/*BASE_LIGHT::base_light show = BASE_LIGHT::base_light();*/

	//LIGHTING_MAPS::lighting_maps show;

	//LIGHT_CASTER::light_caster show;

	//MODEL_LOADING::model_loading show;

	//DEPTH_TESTING::depth_testing show;

	//STENCIL_TESTING::stencil_testing show;

	//Ex_STENCIL_TESTING::ex_stencil_testing show;

	//FRAMEBUFFERS::framebuffers show;

	//POSTPROCESSING::postprocessing show;

	//SSAO::ssao show;

	//DEFERRED_SHADING::deferrd_shading show;

	//DEFERRED_SHADING_VOLUMES::deferred_shading_volumes show;

	HDR::hdr show;
	show.show(message);
    return 0;
}

