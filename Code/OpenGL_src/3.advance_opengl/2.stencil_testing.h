#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Vertices.h"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace STENCIL_TESTING
{
	class stencil_testing
	{
	public:
		stencil_testing();
		~stencil_testing();
		void show();

	private:
		unsigned int SCR_WIDTH;
		unsigned int SCR_HEIGHT;


	};
}